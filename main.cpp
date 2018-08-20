
#include <iostream>
#include <string>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int	main(void)
{
	// get a local ip address and get a socket;
	sf::IpAddress	ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket	socket;
	char	connectionType;

	std::cout << "[s] for server, [c] for client: ";
	std::cin >> connectionType;

	// see if user chose to be the server or client
	if (connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else
		socket.connect(ip, 2000);

	// create the shapes for the "players"
	sf::RectangleShape	rect1, rect2;
	rect1.setSize(sf::Vector2f(20,20));
	rect2.setSize(sf::Vector2f(20,20));
	rect1.setFillColor(sf::Color::Red);
	rect1.setFillColor(sf::Color::Blue);

	// render a basic window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Packets");

	sf::Vector2f	prevPosition, p2Position;

	// don't always wait
	socket.setBlocking(false);

	// this will check if the current window is focused or not
	bool	update = false;

	// while the window is open
	while (window.isOpen())
	{
		sf::Event	Event;
		// check if the window is focused and if it's closed or not
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
				window.close();
			else if (Event.type == sf::Event::GainedFocus)
				update = true;
			else if (Event.type == sf::Event::LostFocus)
				update = false;
		}

		prevPosition = rect1.getPosition();
		// look for key inputs on focused window and then move the player accordinly	
		if (update == true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				rect1.move(0.5f, 0.0f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				rect1.move(-0.5f, 0.0f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				rect1.move(0.0f, -0.5f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				rect1.move(0.0f, 0.5f);
		}
		// create a packet to recieve information
		sf::Packet	packet;
		// if player moved we want to send this packet information
		if (prevPosition != rect1.getPosition())
		{
			// "PIPE" information into the packet
			packet << rect1.getPosition().x << rect1.getPosition().y;
			// send the packet to who ever is listening
			socket.send(packet);
		}
		// now check if a packet was recieved from another player
		socket.receive(packet);
		// this will "unpack" if these values where packed and then move
		// the player 2 according to what was given
		if (packet >> p2Position.x >> p2Position.y)
			rect2.setPosition(p2Position);
		
		// draw the players to the window
		window.draw(rect1);
		window.draw(rect2);
		
		// display the window then clear 
		window.display();
		window.clear();
	}
	return (0);
}
