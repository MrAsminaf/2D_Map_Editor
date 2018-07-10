#include "GUI.h"

GUI::GUI(sf::RectangleShape& rs, BlockTypes& current_block, std::vector<std::vector<int>>& tiles)
	:
	m_spacingBetweenWidgets(7.0f)
{
	InitPanel(rs, current_block, tiles);
}

void GUI::Update()
{
	desktop.Update(0.f);
}

void GUI::HandleEvents(sf::Event sf_event)
{
	desktop.HandleEvent(sf_event);
}

void GUI::InitPanel(sf::RectangleShape& rs, BlockTypes& current_block, std::vector<std::vector<int>>& tiles)
{
	// init sfg window
	m_sfgWindow = sfg::Window::Create();
	m_sfgWindow->SetTitle("Blocks");
	m_sfgWindow->SetStyle(sfg::Window::BACKGROUND);

	// create our box
	m_sfgBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
	m_sfgBox->SetSpacing(m_spacingBetweenWidgets);

	CreateOpenButton(desktop, tiles);

	// make method from that 
	auto generateButton = sfg::Button::Create("Generate");
	void(MapFileGenerator::*pam)(std::vector<std::vector<int>>&) = &MapFileGenerator::Generate;
	MapFileGenerator* alias = &m_generator;
	generateButton->GetSignal(sfg::Widget::OnLeftClick).Connect([pam, alias, &tiles]
	{
		(*alias.*pam)(tiles);
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

	CreateButtonsForChoosingBlocks(rs, current_block);
}

void GUI::CreateButtonsForChoosingBlocks(sf::RectangleShape& rs, BlockTypes& current_block)
{
	BlockTypes enum_grass = BlockTypes::ENUM_GRASS;
	AddButtonForChosingBlock("grass.png", rs, current_block, enum_grass);

	BlockTypes enum_dirt = BlockTypes::ENUM_DIRT;
	AddButtonForChosingBlock("dirt.png", rs, current_block, enum_dirt);

	BlockTypes enum_grass_uldr = BlockTypes::ENUM_GRASS_ULDR;
	AddButtonForChosingBlock("grass_uldr.png", rs, current_block, enum_grass_uldr);

	BlockTypes enum_grass_dltr = BlockTypes::ENUM_GRASS_DLTR;
	AddButtonForChosingBlock("grass_dltr.png", rs, current_block, enum_grass_dltr);

	BlockTypes enum_dirt_dltr = BlockTypes::ENUM_DIRT_DLTR;
	AddButtonForChosingBlock("dirt_dltr.png", rs, current_block, enum_dirt_dltr);

	BlockTypes enum_dirt_tldr = BlockTypes::ENUM_DIRT_TLDR;
	AddButtonForChosingBlock("dirt_tldr.png", rs, current_block, enum_dirt_tldr);

	BlockTypes enum_stone = BlockTypes::ENUM_STONE;
	AddButtonForChosingBlock("stone.png", rs, current_block, enum_stone);

	BlockTypes enum_terrain_platform_left = BlockTypes::ENUM_TERRAIN_PLATFORM_LEFT;
	AddButtonForChosingBlock("terrain_platform_left.png", rs, current_block, enum_terrain_platform_left);
}

void GUI::AddImageToPanel(std::string filepath)
{
	auto sfgImage = sfg::Image::Create();
	sf::Image tempImage;
	tempImage.loadFromFile(filepath);
	sfgImage->SetImage(tempImage);

	sfgImage->GetSignal(sfg::Widget::OnLeftClick).Connect([]
	{
		std::cout << "Kek\n";
	});

	m_scrolledWindowBox->Pack(sfgImage);
}

void GUI::AddButtonForChosingBlock(std::string filepath, sf::RectangleShape& rs, BlockTypes& current_block, BlockTypes& block_being_chosen)
{
	auto sfgImage = sfg::Image::Create();

	sf::Image tempImage;
	tempImage.loadFromFile(filepath);
	sf::Texture texture;
	texture.loadFromFile(filepath);
	sfgImage->SetImage(tempImage);
	sfgImage->SetRequisition(sf::Vector2f(15, 20));

	sfgImage->GetSignal(sfg::Widget::OnLeftClick).Connect([&rs, texture, &current_block, block_being_chosen]
	{
		rs.setTexture(&texture);
		rs.setFillColor(sf::Color(255, 255, 255, 100));
		current_block = block_being_chosen;
	});

	m_scrolledWindowBox->Pack(sfgImage);
}

void GUI::CreateOpenButton(sfg::Desktop& desktop, std::vector<std::vector<int>>& tilesVector)
{
	auto openButton = sfg::Button::Create("Open");
	m_sfgBox->Pack(openButton);

	ExternalMapLoader& mapLoaderAlias = m_mapFromFileLoader;
	openButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop, &mapLoaderAlias, &tilesVector] {

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
		desktop.Add(window);


	//	// Signals.
		destroy_button->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop] {
			// Obtain parent window.
			auto widget = sfg::Context::Get().GetActiveWidget();

			while (widget->GetName() != "Window") {
				widget = widget->GetParent();
			}
			desktop.Remove(widget);
		});

		confirmButton->GetSignal(sfg::Widget::OnLeftClick).Connect([&desktop, &mapLoaderAlias, &tilesVector, entry] {
			mapLoaderAlias.LoadMapFromFile(entry->GetText(), tilesVector);
			auto widget = sfg::Context::Get().GetActiveWidget();

			while (widget->GetName() != "Window") {
				widget = widget->GetParent();
			}
			desktop.Remove(widget);
		});
	});
}
