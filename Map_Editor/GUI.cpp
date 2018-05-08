#include "GUI.h"

GUI::GUI(sf::RectangleShape& rs, TextureLoader::ID& current_block, std::vector<std::vector<int>>& tiles)
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

void GUI::InitPanel(sf::RectangleShape& rs, TextureLoader::ID& current_block, std::vector<std::vector<int>>& tiles)
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
	///
	
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

void GUI::CreateButtonsForChoosingBlocks(sf::RectangleShape& rs, TextureLoader::ID& current_block)
{
	//AddImageToPanel("grass.png");
	TextureLoader::ID enum_grass = TextureLoader::ENUM_GRASS;
	AddButtonForChosingBlock("grass32.png", rs, current_block, enum_grass);

	//AddImageToPanel("dirt.png");
	TextureLoader::ID enum_dirt = TextureLoader::ENUM_DIRT;
	AddButtonForChosingBlock("dirt32.png", rs, current_block, enum_dirt);

	//AddImageToPanel("grass_uldr.png");
	TextureLoader::ID enum_grass_uldr = TextureLoader::ENUM_GRASS_ULDR;
	AddButtonForChosingBlock("grass_uldr32.png", rs, current_block, enum_grass_uldr);

	//AddImageToPanel("grass_dltr.png");
	TextureLoader::ID enum_grass_dltr = TextureLoader::ENUM_GRASS_DLTR;
	AddButtonForChosingBlock("grass_dltr32.png", rs, current_block, enum_grass_dltr);

	TextureLoader::ID enum_dirt_dltr = TextureLoader::ENUM_DIRT_DLTR;
	AddButtonForChosingBlock("dirt_dltr32.png", rs, current_block, enum_dirt_dltr);

	TextureLoader::ID enum_dirt_tldr = TextureLoader::ENUM_DIRT_TLDR;
	AddButtonForChosingBlock("dirt_tldr32.png", rs, current_block, enum_dirt_tldr);

	//AddImageToPanel("stone.png");
	TextureLoader::ID enum_stone = TextureLoader::ENUM_STONE;
	AddButtonForChosingBlock("stone32.png", rs, current_block, enum_stone);
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

void GUI::AddButtonForChosingBlock(std::string filepath, sf::RectangleShape& rs, TextureLoader::ID& current_block, TextureLoader::ID& block_being_chosen)
{
	auto sfgImage = sfg::Image::Create();

	/*sf::Sprite tempSprite;
	sf::Texture tempTexture;
	tempTexture.loadFromFile(filepath);
	tempSprite.setTexture(tempTexture);
	tempSprite.scale(sf::Vector2f(2, 2));*/

	sf::Image tempImage;
	tempImage.loadFromFile(filepath);
	sf::Texture texture;
	texture.loadFromFile(filepath);
	sfgImage->SetImage(tempImage);
	sfgImage->SetRequisition(sf::Vector2f(15, 40));

	sfgImage->GetSignal(sfg::Widget::OnLeftClick).Connect([&rs, texture, &current_block, block_being_chosen]
	{
		rs.setTexture(&texture);
		rs.setFillColor(sf::Color(255, 255, 255, 100));
		current_block = block_being_chosen;
	});

	m_scrolledWindowBox->Pack(sfgImage);

	//auto button = sfg::Button::Create(label);
	//sf::Texture texture;
	//texture.loadFromFile(filepath);
	//button->GetSignal(sfg::Widget::OnLeftClick).Connect([&rs, texture, &current_block, block_being_chosen]
	//{
	//	rs.setTexture(&texture);
	//	rs.setFillColor(sf::Color(255, 255, 255, 100));
	//	current_block = block_being_chosen;
	//});
	//m_scrolledWindowBox->Pack(button);
	//m_scrolledWindowBox->Pack(sfg::Separator::Create());
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
