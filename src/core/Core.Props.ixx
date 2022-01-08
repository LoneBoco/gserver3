export module graal.core:props;

import graal.packet;

import "common.h";

import <sstream>;
import <iterator>;
import <variant>;
import <initializer_list>;

/*
template <class T>
concept GeneratesPropList = requires(T a) {
	{ a.generateProps() } -> std::vector<uint8_t>;
};
*/


export namespace graal::core
{

enum class PropertyType
{
	INVALID = 0,
	SIGNED,
	UNSIGNED,
	FLOAT,
	STRING,

	COUNT
};

constexpr uint16_t INVALID_PROPERTY = 0xFFFF;

class Property;
class PropertyGroup;
using PropertyImportFunction = std::function< std::size_t(const packet::PacketData&, Property&) >;
//using PropertyImportFunction = std::function< void(packet::PacketIterRange&, Property&) >;
using PropertyExportFunction = std::function< packet::PacketData(const PropertyGroup&) >;

class Property
{
public:
	constexpr Property(const PropertyType t = PropertyType::INVALID) : m_type(t)
	{
		switch (t)
		{
		case PropertyType::SIGNED:
			m_value = static_cast<int64_t>(0);
			break;
		case PropertyType::UNSIGNED:
			m_value = static_cast<uint64_t>(0);
			break;
		case PropertyType::FLOAT:
			m_value = static_cast<float>(0.0f);
			break;
		case PropertyType::STRING:
			m_value = "";
		}
	}

	Property(const Property& a) :m_type(a.m_type), m_value(a.m_value) {}
	Property(Property&& o) noexcept
		: m_type(o.m_type), m_value(o.m_value), m_isDirty(o.m_isDirty)
	{
		o.m_type = PropertyType::INVALID;
		o.m_value = 0;
		o.m_isDirty = false;
	}
	~Property() {}

	Property& operator=(const Property& other)
	{
		m_type = other.m_type;
		m_value = other.m_value;
		m_isDirty = other.m_isDirty;
		return *this;
	}
	Property& operator=(Property&& other) noexcept
	{
		m_type = other.m_type;
		m_value = other.m_value;
		m_isDirty = other.m_isDirty;

		other.m_type = PropertyType::INVALID;
		other.m_value = static_cast<int64_t>(0);
		other.m_isDirty = false;
		return *this;
	}

	constexpr bool operator==(const Property& other) const
	{
		return m_type == other.m_type && m_value == other.m_value;
	}

	constexpr bool operator!=(const Property& other) const
	{
		return m_type != other.m_type || m_value != other.m_value;
	}

	Property& Set(const int64_t value)
	{
		assert(m_type == PropertyType::SIGNED && std::get_if<int64_t>(&m_value) != nullptr);

		if (std::get<int64_t>(m_value) != value)
			m_isDirty = true;

		m_value = value;

		//if (m_isDirty)
		//	UpdateDispatch.Post(m_id);

		return *this;
	}
	Property& Set(const uint64_t value)
	{
		assert(m_type == PropertyType::UNSIGNED && std::get_if<uint64_t>(&m_value) != nullptr);

		if (std::get<uint64_t>(m_value) != value)
			m_isDirty = true;

		m_value = value;

		//if (m_isDirty)
		//	UpdateDispatch.Post(m_id);

		return *this;
	}
	Property& Set(const float value)
	{
		assert(m_type == PropertyType::FLOAT && std::get_if<float>(&m_value) != nullptr);

		if (std::get<float>(m_value) != value)
			m_isDirty = true;

		m_value = value;

		//if (m_isDirty)
		//	UpdateDispatch.Post(m_id);

		return *this;
	}
	Property& Set(const std::string& value)
	{
		assert(m_type == PropertyType::STRING && std::get_if<std::string>(&m_value) != nullptr);

		if (std::get<std::string>(m_value) != value)
			m_isDirty = true;

		m_value = value;

		//if (m_isDirty)
		//	UpdateDispatch.Post(m_id);

		return *this;
	}
	Property& SetAsType(const PropertyType type, const std::string& value)
	{
		if (type == PropertyType::STRING)
		{
			Set(value);
			return *this;
		}

		std::istringstream str(value);
		switch (type)
		{
		case PropertyType::SIGNED:
			int64_t s;
			str >> s;
			Set(s);
			break;
		case PropertyType::UNSIGNED:
			uint64_t u;
			str >> u;
			Set(u);
			break;
		case PropertyType::FLOAT:
			float f;
			str >> f;
			Set(f);
			break;
		}
		return *this;
	}

	Property& operator=(const int64_t value)
	{
		Set(value);
		return *this;
	}
	Property& operator=(const uint64_t value)
	{
		Set(value);
		return *this;
	}
	Property& operator=(const float value)
	{
		Set(value);
		return *this;
	}
	Property& operator=(const std::string& value)
	{
		Set(value);
		return *this;
	}

	int64_t GetSigned() const
	{
		switch (m_type)
		{
			case PropertyType::SIGNED:
				return std::get<int64_t>(m_value);
			case PropertyType::UNSIGNED:
				return static_cast<int64_t>(std::get<uint64_t>(m_value));
			case PropertyType::FLOAT:
				return static_cast<int64_t>(std::get<float>(m_value));
			case PropertyType::STRING:
			{
				std::istringstream str(std::get<std::string>(m_value));
				int64_t r;
				str >> r;
				return r;
			}
		}
		return 0;
	}
	uint64_t GetUnsigned() const
	{
		switch (m_type)
		{
			case PropertyType::SIGNED:
				return static_cast<uint64_t>(std::get<int64_t>(m_value));
			case PropertyType::UNSIGNED:
				return std::get<uint64_t>(m_value);
			case PropertyType::FLOAT:
				return static_cast<uint64_t>(std::get<float>(m_value));
			case PropertyType::STRING:
			{
				std::istringstream str(std::get<std::string>(m_value));
				uint64_t r;
				str >> r;
				return r;
			}
		}
		return 0;
	}
	float GetFloat() const
	{
		switch (m_type)
		{
			case PropertyType::SIGNED:
				return static_cast<float>(std::get<int64_t>(m_value));
			case PropertyType::UNSIGNED:
				return static_cast<float>(std::get<uint64_t>(m_value));
			case PropertyType::FLOAT:
				return std::get<float>(m_value);
			case PropertyType::STRING:
			{
				std::istringstream str(std::get<std::string>(m_value));
				float r;
				str >> r;
				return r;
			}
		}
		return 0;
	}
	std::string GetString() const
	{
		std::stringstream str;
		switch (m_type)
		{
			case PropertyType::SIGNED:
				str << std::get<int64_t>(m_value);
				break;
			case PropertyType::UNSIGNED:
				str << std::get<uint64_t>(m_value);
				break;
			case PropertyType::FLOAT:
				str << std::get<float>(m_value);
				break;
			case PropertyType::STRING:
				return std::get<std::string>(m_value);
		}
		return str.str();
	}

	constexpr const PropertyType GetType() const { return m_type; }
	void SetType(const PropertyType t) { m_type = t; }

	constexpr const bool GetIsDirty() const { return m_isDirty; }
	void SetIsDirty(bool dirty) { m_isDirty = dirty; }

public:
	//EventDispatcher<uint16_t> UpdateDispatch;

public:
	static PropertyType TypeFromString(const std::string& type)
	{
		if (boost::iequals(type, "signed"))
			return PropertyType::SIGNED;
		if (boost::iequals(type, "unsigned"))
			return PropertyType::UNSIGNED;
		if (boost::iequals(type, "float"))
			return PropertyType::FLOAT;
		if (boost::iequals(type, "string"))
			return PropertyType::STRING;

		return PropertyType::INVALID;
	}

protected:
	PropertyType m_type = PropertyType::INVALID;
	std::variant<int64_t, uint64_t, float, std::string> m_value = static_cast<int64_t>(0);
	bool m_isDirty = false;
};


class PropertyGroup
{
public:
	PropertyGroup() = delete;
	~PropertyGroup() = default;

	PropertyGroup(const Property& prop)
	{
		m_properties.push_back(prop);
	}

	PropertyGroup(Property&& prop) noexcept
	{
		m_properties.push_back(std::move(prop));
	}

	PropertyGroup(const PropertyGroup& group)
		: m_id(group.m_id), m_properties(group.m_properties), ImportFunction(group.ImportFunction), ExportFunction(group.ExportFunction)
	{}

	PropertyGroup(PropertyGroup&& group) noexcept
		: m_id(group.m_id), m_properties(std::move(group.m_properties)), ImportFunction(group.ImportFunction), ExportFunction(group.ExportFunction)
	{}

	PropertyGroup(uint16_t id, Property prop, PropertyImportFunction f_import, PropertyExportFunction f_export)
		: m_id(id), ImportFunction(f_import), ExportFunction(f_export)
	{
		m_properties.push_back(prop);
	}

	PropertyGroup(uint16_t id, std::initializer_list<Property> props, PropertyImportFunction f_import, PropertyExportFunction f_export)
		: m_id(id), m_properties(props), ImportFunction(f_import), ExportFunction(f_export)
	{}

	PropertyGroup& operator=(const PropertyGroup& other)
	{
		m_id = other.m_id;
		m_properties = other.m_properties;
		ImportFunction = other.ImportFunction;
		ExportFunction = other.ExportFunction;
		return *this;
	}
	PropertyGroup& operator=(PropertyGroup&& other)
	{
		m_id = other.m_id;
		m_properties = std::move(other.m_properties);
		ImportFunction = std::move(other.ImportFunction);
		ExportFunction = std::move(other.ExportFunction);
		return *this;
	}
	constexpr bool operator==(const PropertyGroup& other) const { return m_id == other.m_id && m_properties == other.m_properties; }
	constexpr bool operator!=(const PropertyGroup& other) const { return m_id != other.m_id || m_properties != other.m_properties; }
	constexpr bool operator<(const PropertyGroup& other) const { return m_id < other.m_id; }

public:
	constexpr Property& operator[](std::size_t index)
	{
		assert(index <= m_properties.size());
		return m_properties.at(index);
	}

	constexpr const Property& operator[](std::size_t index) const
	{
		assert(index <= m_properties.size());
		return m_properties.at(index);
	}

	constexpr operator Property& ()
	{
		return this->operator[](0);
	}

	constexpr operator const Property& () const
	{
		return this->operator[](0);
	}

	constexpr bool IsGroup() const { return m_properties.size() > 1; }
	constexpr uint16_t GetID() const { return m_id; }

public:
	PropertyImportFunction ImportFunction;
	PropertyExportFunction ExportFunction;

protected:
	uint16_t m_id;
	std::vector<Property> m_properties;
};


class ObjectProperties
{
	using property_entry = PropertyGroup;
	using property_map = std::map<uint16_t, std::shared_ptr<property_entry>>;

public:

#pragma region IteratorDirty
	class IteratorDirty
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = property_entry;
		using difference_type = int;
		using pointer = property_entry*;
		using reference = property_entry&;

	public:
		IteratorDirty(ObjectProperties& properties, property_map::iterator iterator)
		{
			m_begin = properties.m_properties.begin();
			m_end = properties.m_properties.end();
			m_iter = iterator;
		}
		IteratorDirty(IteratorDirty& other) : m_begin(other.m_begin), m_end(other.m_end), m_iter(other.m_iter) {}

	public:
		bool operator==(const IteratorDirty& other) const { return m_iter == other.m_iter; }
		bool operator!=(const IteratorDirty& other) const { return m_iter != other.m_iter; }
		reference operator*() { return *m_iter->second; }
		pointer operator->() { return m_iter->second.get(); }

		IteratorDirty operator++()
		{
			IteratorDirty i{ *this };
			if (m_iter == m_end)
				return i;

			++m_iter;
			while (m_iter != m_end)
			{
				auto& group = *m_iter->second;
				if (!group.IsGroup() && group[0].GetIsDirty())
					break;
				if (group.IsGroup())
				{
					// TODO: Flatten this whole range first!
					break;
				}
				++m_iter;
			}
			return i;
		}

		IteratorDirty operator++(int)
		{
			if (m_iter == m_end)
				return *this;

			++m_iter;
			while (m_iter != m_end)
			{
				// TODO: Flatten this whole range first!
				if ((*m_iter->second)[0].GetIsDirty())
					break;
				++m_iter;
			}
			return *this;
		}

	protected:
		property_map::iterator m_begin;
		property_map::iterator m_iter;
		property_map::iterator m_end;
	};
#pragma endregion

public:
	ObjectProperties() {}
	~ObjectProperties()
	{
		m_properties.clear();
	}

	ObjectProperties(const ObjectProperties& other) : m_properties(other.m_properties) {}

	ObjectProperties(ObjectProperties&& other) noexcept
		: m_properties(std::move(other.m_properties))
	{
		other.m_properties.clear();
	}

	ObjectProperties(std::initializer_list<property_entry> props)
	{
		for (auto& group : props)
			m_properties[group.GetID()] = std::make_shared<property_entry>(std::move(group));
	}

	ObjectProperties& operator=(ObjectProperties&& other) noexcept
	{
		m_properties = std::move(other.m_properties);
		other.m_properties.clear();
		return *this;
	}
	ObjectProperties& operator=(const ObjectProperties& other)
	{
		m_properties.clear();
		m_properties = other.m_properties;
		return *this;
	}

	//! Returns an Property.
	//! \param id The id number of the Property to get.
	//! \return A pointer to the Property structure, or nullptr if the Property was not found.
	property_map::mapped_type Get(const uint16_t id)
	{
		auto i = m_properties.find(id);
		if (i == m_properties.end()) return nullptr;
		return i->second;
	}

	//! Returns an Property.
	//! \param id The id number of the Property to get.
	//! \return A pointer to the Property structure, or nullptr if the Property was not found.
	const property_map::mapped_type Get(const uint16_t id) const
	{
		auto i = m_properties.find(id);
		if (i == m_properties.end()) return nullptr;
		return i->second;
	}

	property_map::mapped_type operator[](uint16_t index) { return Get(index); }
	const property_map::mapped_type operator[](uint16_t index) const { return Get(index); }

	//! Returns the Property map.
	//! \return The Property map.
	property_map& GetMap() { return m_properties; }

	//! Returns an iterator to iterate over dirty Properties.
	IteratorDirty GetDirtyBegin() { return IteratorDirty(*this, m_properties.begin()); }
	IteratorDirty GetDirtyEnd() { return IteratorDirty(*this, m_properties.end()); }

	//! Returns if we have any dirty Properties.
	bool HasDirty() const
	{
		return std::any_of(m_properties.begin(), m_properties.end(), [](const auto& v) -> bool
			{
				// TODO: Flatten somehow!
				return (*v.second)[0].GetIsDirty();
			});
	}

	//! Clears the dirty flag and dispatches events for the Properties.
	void ClearDirty()
	{
		for (auto& [key, value] : m_properties)
		{
			if ((*value)[0].GetIsDirty())
			{
				(*value)[0].SetIsDirty(false);
				//value->UpdateDispatch.Post(key);
				//DirtyUpdateDispatch.Post(key);
			}
		}
	}

	//EventDispatcher<uint16_t> DirtyUpdateDispatch;

public:
	property_map::iterator begin() { return m_properties.begin(); };
	property_map::iterator end() { return m_properties.end(); }
	property_map::const_iterator begin() const { return m_properties.begin(); }
	property_map::const_iterator end() const { return m_properties.end(); }

private:

	//! Gets or creates an Property.
	/*
	std::shared_ptr<Property> getOrCreateProperty(uint16_t id = -1)
	{
		// Find the attribute.  Determine if we need to delete it.
		std::shared_ptr<Property> a = Get(id);
		if (a != nullptr) return a;

		a = std::make_shared<Property>(PropertyType::UNSIGNED);
		assignId(id, *a);

		m_properties.insert(std::pair<uint16_t, std::shared_ptr<Property>>(a->GetId(), a));
		return a;
	}
	*/

	std::map<uint16_t, std::shared_ptr<property_entry>> m_properties;

public:
	class Dirty
	{
	public:
		Dirty(ObjectProperties& properties) { m_properties = &properties; }
		IteratorDirty begin() { return m_properties->GetDirtyBegin(); }
		IteratorDirty end() { return m_properties->GetDirtyEnd(); }

	protected:
		ObjectProperties* m_properties;
	};
};

} // end namespace graal::core


export namespace graal::core::props::in
{

template <std::size_t N>
std::size_t GraalByte(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::UNSIGNED || p.GetType() == PropertyType::SIGNED);

	if (p.GetType() == PropertyType::UNSIGNED)
	{
		uint64_t data;
		d >> packet::ReadGraalByte<N>(data);
		p.Set(data);
	}
	else
	{
		int64_t data;
		d >> packet::ReadGraalByte<N>(data);
		p.Set(data);
	}

	return N;
}
auto GraalByte1(const packet::PacketData& d, Property& p) -> auto { return GraalByte<1>(d, p); }
auto GraalByte2(const packet::PacketData& d, Property& p) -> auto { return GraalByte<2>(d, p); }
auto GraalByte3(const packet::PacketData& d, Property& p) -> auto { return GraalByte<3>(d, p); }
auto GraalByte4(const packet::PacketData& d, Property& p) -> auto { return GraalByte<4>(d, p); }
auto GraalByte5(const packet::PacketData& d, Property& p) -> auto { return GraalByte<5>(d, p); }


template <std::size_t N>
std::size_t RawByte(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::UNSIGNED || p.GetType() == PropertyType::SIGNED);

	if (p.GetType() == PropertyType::UNSIGNED)
	{
		uint64_t data;
		d >> packet::ReadByte<N>(data);
		p.Set(data);
	}
	else if (p.GetType() == PropertyType::SIGNED)
	{
		int64_t data;
		d >> packet::ReadByte<N>(data);
		p.Set(data);
	}

	return N;
}
auto RawByte1(const packet::PacketData& d, Property& p) -> auto { return RawByte<1>(d, p); }
auto RawByte2(const packet::PacketData& d, Property& p) -> auto { return RawByte<2>(d, p); }
auto RawByte3(const packet::PacketData& d, Property& p) -> auto { return RawByte<3>(d, p); }
auto RawByte4(const packet::PacketData& d, Property& p) -> auto { return RawByte<4>(d, p); }
auto RawByte5(const packet::PacketData& d, Property& p) -> auto { return RawByte<5>(d, p); }


template <std::size_t N>
std::size_t ClassicString(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::STRING);

	std::string data;
	d >> packet::ReadClassicString<N>(data);
	p.Set(data);

	return N + std::ranges::size(data);
}
auto ClassicString1(const packet::PacketData& d, Property& p) -> auto { return ClassicString<1>(d, p); }
auto ClassicString2(const packet::PacketData& d, Property& p) -> auto { return ClassicString<2>(d, p); }
auto ClassicString3(const packet::PacketData& d, Property& p) -> auto { return ClassicString<3>(d, p); }
auto ClassicString4(const packet::PacketData& d, Property& p) -> auto { return ClassicString<4>(d, p); }
auto ClassicString5(const packet::PacketData& d, Property& p) -> auto { return ClassicString<5>(d, p); }


template <std::size_t N>
std::size_t String(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::STRING);

	std::string data;
	d >> packet::ReadString<N>(data);
	p.Set(data);

	return N + std::ranges::size(data);
}
auto String1(const packet::PacketData& d, Property& p) -> auto { return String<1>(d, p); }
auto String2(const packet::PacketData& d, Property& p) -> auto { return String<2>(d, p); }
auto String3(const packet::PacketData& d, Property& p) -> auto { return String<3>(d, p); }
auto String4(const packet::PacketData& d, Property& p) -> auto { return String<4>(d, p); }
auto String5(const packet::PacketData& d, Property& p) -> auto { return String<5>(d, p); }


std::size_t RawString(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::STRING);

	std::string data{ std::begin(d), std::end(d) };
	p.Set(data);
	return std::ranges::size(data);
}


std::size_t FloatPosition(const packet::PacketData& d, Property& p)
{
	assert(p.GetType() == PropertyType::FLOAT);

	int8_t data;
	d >> packet::ReadGraalByte<1>(data);
	p.Set(data / 2.0f);

	return 1;
}

} // end namespace graal::core::props::in

export namespace graal::core::props::out
{

template <std::size_t N>
packet::PacketData GraalByte(const PropertyGroup& p)
{
	packet::PacketData result;
	result << packet::WriteGraalByte<N>(p[0].GetUnsigned());
	return result;
}
auto GraalByte1(const PropertyGroup& p) -> auto { return GraalByte<1>(p); }
auto GraalByte2(const PropertyGroup& p) -> auto { return GraalByte<2>(p); }
auto GraalByte3(const PropertyGroup& p) -> auto { return GraalByte<3>(p); }
auto GraalByte4(const PropertyGroup& p) -> auto { return GraalByte<4>(p); }
auto GraalByte5(const PropertyGroup& p) -> auto { return GraalByte<5>(p); }


template <std::size_t N>
packet::PacketData RawByte(const PropertyGroup& p)
{
	packet::PacketData result;
	result << packet::WriteByte<N>(p[0].GetUnsigned());
	return result;
}
auto RawByte1(const PropertyGroup& p) -> auto { return RawByte<1>(p); }
auto RawByte2(const PropertyGroup& p) -> auto { return RawByte<2>(p); }
auto RawByte3(const PropertyGroup& p) -> auto { return RawByte<3>(p); }
auto RawByte4(const PropertyGroup& p) -> auto { return RawByte<4>(p); }
auto RawByte5(const PropertyGroup& p) -> auto { return RawByte<5>(p); }


template <std::size_t N>
packet::PacketData ClassicString(const PropertyGroup& p)
{
	packet::PacketData result;
	auto str = p[0].GetString();
	result << packet::WriteGraalByte<N>(str.size()) << str;
	return result;
}
auto ClassicString1(const PropertyGroup& p) -> auto { return ClassicString<1>(p); }
auto ClassicString2(const PropertyGroup& p) -> auto { return ClassicString<2>(p); }
auto ClassicString3(const PropertyGroup& p) -> auto { return ClassicString<3>(p); }
auto ClassicString4(const PropertyGroup& p) -> auto { return ClassicString<4>(p); }
auto ClassicString5(const PropertyGroup& p) -> auto { return ClassicString<5>(p); }


template <std::size_t N>
packet::PacketData String(const PropertyGroup& p)
{
	packet::PacketData result;
	auto str = p[0].GetString();
	result << packet::WriteByte<N>(str.size()) << str;
	return result;
}
auto String1(const PropertyGroup& p) -> auto { return String<1>(p); }
auto String2(const PropertyGroup& p) -> auto { return String<2>(p); }
auto String3(const PropertyGroup& p) -> auto { return String<3>(p); }
auto String4(const PropertyGroup& p) -> auto { return String<4>(p); }
auto String5(const PropertyGroup& p) -> auto { return String<5>(p); }


packet::PacketData RawString(const PropertyGroup& p)
{
	packet::PacketData result;
	auto str = p[0].GetString();
	result << str;
	return result;
}


packet::PacketData FloatPosition(const PropertyGroup& p)
{
	packet::PacketData result;
	result << packet::WriteGraalByte<1>(static_cast<uint64_t>(p[0].GetFloat() * 2));
	return result;
}

} // end namespace graal::core::props::out
