export module graal.packet.types.server:levelboard;

import "common.h";
import graal.packet;


export namespace graal::packet::server
{

	// [UBYTE5 modtime][SBYTE1 x (float)][SBYTE1 y (float)][STRING level]
	class LevelBoard : protected Packet
	{
	public:
		LevelBoard()
		{}

		LevelBoard(const packet::PacketData&& packet)
		{
			// TODO.
		}

		~LevelBoard() override {}

	public:
		operator packet::PacketData() const override
		{
			packet::PacketData result;
			// Board changes.
			return result;
		}

	public:
		// Board changes.
	};

} // end namespace graal::packet::client
