#include <enet/enet.h>
#include <string>
#include <iostream>
#include <random>

using namespace std;

constexpr int MAX_NUMBER = 10;

ENetHost* NetHost = nullptr;
ENetPeer* Peer = nullptr;
bool IsServer = false;
enum PacketHeaderTypes
{
    PHT_Invalid = 0,
    PHT_GUESS,
    PHT_WIN,
    PHT_WRONG
};

struct GamePacket
{
    GamePacket() {}
    PacketHeaderTypes Type = PHT_Invalid;
};

struct GuessPacket : public GamePacket
{
    int m_guess;

    GuessPacket(int guess)
    {
        Type = PHT_GUESS;
        m_guess = guess;

    }
    
   
};

struct WinPacket : public GamePacket
{

    WinPacket()
    {
        Type = PHT_WIN;

    }

};

struct WrongPacket : public GamePacket
{

    WrongPacket()
    {
        Type = PHT_WRONG;

    }


};

void BroadcastPacket(ENetPacket * packet) {
    enet_host_broadcast(NetHost, 0, packet);
    enet_host_flush(NetHost);
    delete packet;
}

int getGoodInt() {
    std::cout << "Enter a guess within the range of 1 and " << MAX_NUMBER << '\n';
    int input;
    std::cin >> input;
    while (true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "A number wasn't entered. Please enter a positive number within the range of 1 and " << MAX_NUMBER<< endl;
            std::cin >> input;
        }
        else if (input < 1 || input > MAX_NUMBER) {
            std::cout << "An invalid number was entered. Please enter a positive number within the range of 1 and " << MAX_NUMBER << endl;
            std::cin >> input;
        }
        else return input;
    }
}

//can pass in a peer connection if wanting to limit
bool CreateServer()
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    NetHost = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool CreateClient()
{
    NetHost = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}

bool AttemptConnectToServer()
{
    ENetAddress address;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    Peer = enet_host_connect(NetHost, &address, 2, 0);
    return Peer != nullptr;
}

void HandleReceivePacketServer(const ENetEvent& event, int randomNumber)
{
    GamePacket* RecGamePacket = (GamePacket*)(event.packet->data);
    if (RecGamePacket)
    {
        std::cout << "Received Game Packet " << endl;

        switch (RecGamePacket->Type)
        {
            case PHT_GUESS:
            {
                GuessPacket* gp = (GuessPacket*)(event.packet->data);
                std::cout << "The user guessed " << gp->m_guess << endl;
                if (gp->m_guess == randomNumber)
                {
                    std::cout << "The user guessed correctly" << endl;
                    WinPacket* win = new WinPacket;
                    ENetPacket* packet = enet_packet_create(win,
                        sizeof(WinPacket),
                        ENET_PACKET_FLAG_RELIABLE);
                    BroadcastPacket(packet);

                    //TODO: End Game on server

                }
                else
                {
                    std::cout << "The user guessed incorrectly" << endl;
                    WrongPacket* wrong = new WrongPacket;
                    ENetPacket* packet = enet_packet_create(wrong,
                        sizeof(wrong),
                        ENET_PACKET_FLAG_RELIABLE);
                    
                    BroadcastPacket(packet);

                }

                           
            }
            

            //Case isn't needed since we only have one possible answer, just implementing it if we were to change how our system works 

        }
    }
    else
    {
        std::cout << "Invalid Packet " << endl;
        //TODO: send failure packet
    }

    /* Clean up the packet now that we're done using it. */
    enet_packet_destroy(event.packet);
    {
        enet_host_flush(NetHost);
    }
}

void HandleReceivePacketClient(const ENetEvent& event)
{
    GamePacket* RecGamePacket = (GamePacket*)(event.packet->data);
    if (RecGamePacket)
    {

        switch (RecGamePacket->Type)
        {
            case PHT_WIN:
            {
                std::cout << "You have guessed correctly! Congratulations" << endl;
                //TODO: END THE GAME on client
                break;
            }
            case PHT_WRONG:
            {
                std::cout << "You have guessed incorrectly, please guess again" << endl;
                GuessPacket* guess = new GuessPacket(getGoodInt());
                ENetPacket* packet = enet_packet_create(guess,
                    sizeof(GuessPacket),
                    ENET_PACKET_FLAG_RELIABLE);
                BroadcastPacket(packet);
                break;

            }
        }
    }
    else
    {
        std::cout << "Invalid Packet " << endl;


    }

    /* Clean up the packet now that we're done using it. */
    enet_packet_destroy(event.packet);
    {
        enet_host_flush(NetHost);
    }
}



void ServerProcessPackets(int randomNumber)
{
    while (1)
    {
        ENetEvent event;
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                cout << "A new client connected from "
                    << event.peer->address.host
                    << ":" << event.peer->address.port
                    << endl;
                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacketServer(event, randomNumber);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << "disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                //notify remaining player that the game is done due to player leaving
            }
        }
    }
}

void ClientProcessPackets()
{
    GuessPacket* guessPacket;
    while (1)
    {
        ENetEvent event;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    cout << "Connection succeeded " << endl;
                    int guess = getGoodInt();
                    guessPacket = new GuessPacket(guess);
                    ENetPacket* packet = enet_packet_create(guessPacket,
                        sizeof(GuessPacket),
                        ENET_PACKET_FLAG_RELIABLE);
                    BroadcastPacket(packet);

                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                HandleReceivePacketClient(event);
                break;
            }
        }
    }
}

int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    cout << "1) Create Server " << endl;
    cout << "2) Create Client " << endl;
    int UserInput;
    cin >> UserInput;
    if (UserInput == 1)
    {
        srand(time(0));
        int randomNumber = (rand() % MAX_NUMBER) + 1;
        cout << randomNumber << " is the target number\n";
        if (!CreateServer())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server.\n");
            exit(EXIT_FAILURE);
        }

        IsServer = true;
        cout << "waiting for players to join..." << endl;
        ServerProcessPackets(randomNumber);
    }
    else if (UserInput == 2)
    {
        if (!CreateClient())
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet client host.\n");
            exit(EXIT_FAILURE);
        }


        if (!AttemptConnectToServer())
        {
            fprintf(stderr,
                "No available peers for initiating an ENet connection.\n");
            exit(EXIT_FAILURE);
        }

        ClientProcessPackets();

        //handle possible connection failure
        {
            //enet_peer_reset(Peer);
            //cout << "Connection to 127.0.0.1:1234 failed." << endl;
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }
    
    if (NetHost != nullptr)
    {
        enet_host_destroy(NetHost);
    }
    
    return EXIT_SUCCESS;
}