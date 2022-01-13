export module graal.core;
export import :position;
export import :flags;
export import :base64;
export import :concepts;
export import :props;
export import :random;
export import :log;
export import graal.core.events;


export namespace graal
{

uint16_t ENUMID(auto e)
{
	return static_cast<uint16_t>(e);
}

}
