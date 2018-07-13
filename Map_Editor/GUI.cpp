#include "GUI.h"

sfg::Box::Ptr GUI::m_scrolledWindowBox;

GUI::GUI()
	:
	m_spacingBetweenWidgets(7.0f)
{
	InitPanel();
}

void GUI::Update()
{
	desktop.Update(0.f);
}

void GUI::HandleEvents(sf::Event sf_event)
{
	desktop.HandleEvent(sf_event);
}

void GUI::InitPanel()
{
	// init sfg window
	m_sfgWindow = sfg::Window::Create();
	m_sfgWindow->SetStyle(sfg::Window::BACKGROUND);

	// create our box
	m_sfgBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	m_sfgBox->SetSpacing(m_spacingBetweenWidgets);

	CreateOpenButton();

	// make method from that 
	auto generateButton = sfg::Button::Create("Generate");
	void(MapFileGenerator::*pam)() = &MapFileGenerator::Generate;
	MapFileGenerator* alias = &m_generator;
	generateButton->GetSignal(sfg::Widget::OnLeftClick).Connect([pam, alias]
	{
		(*alias.*pam)();
	});
	m_sfgBox->Pack(generateButton);
	
	//box for scrolled window
	m_scrolledWindowBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	m_scrolledWindowBox->SetSpacing(m_spacingBetweenWidgets);

	// add scrollview
	auto scrolledWindow = sfg::ScrolledWindow::Create();
	scrolledWindow->SetScrollbarPolicy(sfg::ScrolledWindow::HORIZONTAL_NEVER | sfg::ScrolledWindow::VERTICAL_AUTOMATIC);
	scrolledWindow->AddWithViewport(m_scrolledWindowBox);
	scrolledWindow->SetRequisition(sf::Vector2f(60.f, 400.f));
	m_sfgBox->Pack(scrolledWindow);

	m_sfgWindow->Add(m_sfgBox);
	desktop.Add(m_sfgWindow);

	CreateButtonsForChoosingBlocks();
}

void GUI::CreateButtonsForChoosingBlocks()
{
	BlockTypes enum_grass = BlockTypes::ENUM_GRASS;
	AddButtonForChosingBlock("grass.png", enum_grass);

	BlockTypes enum_dirt = BlockTypes::ENUM_DIRT;
	AddButtonForChosingBlock("dirt.png", enum_dirt);

	BlockTypes enum_grass_uldr = BlockTypes::ENUM_GRASS_ULDR;
	AddButtonForChosingBlock("grass_uldr.png", enum_grass_uldr);

	BlockTypes enum_grass_dltr = BlockTypes::ENUM_GRASS_DLTR;
	AddButtonForChosingBlock("grass_dltr.png", enum_grass_dltr);

	BlockTypes enum_dirt_dltr = BlockTypes::ENUM_DIRT_DLTR;
	AddButtonForChosingBlock("dirt_dltr.png", enum_dirt_dltr);

	BlockTypes enum_dirt_tldr = BlockTypes::ENUM_DIRT_TLDR;
	AddButtonForChosingBlock("dirt_tldr.png", enum_dirt_tldr);

	BlockTypes enum_stone = BlockTypes::ENUM_STONE;
	AddButtonForChosingBlock("stone.png", enum_stone);

	BlockTypes enum_terrain_platform_left = BlockTypes::ENUM_TERRAIN_PLATFORM_LEFT;
	AddButtonForChosingBlock("terrain_platform_left.png", enum_terrain_platform_left);
}

void GUI::AddButtonForChosingBlock(const std::string& filepath, const BlockTypes& block_being_chosen)
{
	auto sfgImage = sfg::Image::Create();

	sf::Image tempImage;
	tempImage.loadFromFile(filepath);
	sf::Texture texture;
	texture.loadFromFile(filepath);
	sfgImage->SetImage(tempImage);
	sfgImage->SetRequisition(sf::Vector2f(15, 20));

	sfgImage->GetSignal(sfg::Widget::OnLeftClick).Connect([texture, block_being_chosen]
	{
		Interface::GetMouseHighlight().setTexture(&texture);
		Interface::GetMouseHighlight().setFillColor(sf::Color(255, 255, 255, 100));
		Interface::GetCurrentBlock() = block_being_chosen;
	});

	m_scrolledWindowBox->Pack(sfgImage);
}

void GUI::CreateOpenButton()
{
	auto openButton = sfg::Button::Create("Open");
	m_sfgBox->Pack(openButton);

	ExternalMapLoader& mapLoaderAlias = m_mapFromFileLoader;
	sfg::Desktop& desktop_alias = desktop;
	openButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop_alias, &mapLoaderAlias] {

		auto window = sfg::Window::Create();
		window->SetTitle("Open File");
		window->SetPosition(sf::Vector2f(200, 200));
		std::cout << window->GetRequisition().x << std::endl;

		auto label = sfg::Label::Create();
		label->SetText("Enter name of the file");

		auto entry = sfg::Entry::Create();
		entry->SetRequisition(sf::Vector2f(80.f, 0.f));

		auto confirmButton = sfg::Button::Create("Load");

	//	// Layout.
		auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
		auto destroy_button = sfg::Button::Create("Close");
		box->Pack(destroy_button);

		box->Pack(label);
		box->Pack(entry);
		box->Pack(confirmButton);

		window->Add(box);
		desktop_alias.Add(window);


	//	// Signals.
		destroy_button->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop_alias] {
			// Obtain parent window.
			auto widget = sfg::Context::Get().GetActiveWidget();

			while (widget->GetName() != "Window") {
				widget = widget->GetParent();
			}
			desktop_alias.Remove(widget);
		});

		confirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop_alias, &mapLoaderAlias, entry] {
			mapLoaderAlias.LoadMapFromFile(entry->GetText(), Interface::GetTilesContainer());
			auto widget = sfg::Context::Get().GetActiveWidget();

			while (widget->GetName() != "Window") {
				widget = widget->GetParent();
			}
			desktop_alias.Remove(widget);
		});
	});
}
