//////////////////////////////////////////////////////////////////////
//                                                                  //
//                     Created by RoseKavalier:                     //
//                     rosekavalierhc@gmail.com                     //
//                       Created: 2019-12-05                        //
//        ***You may use or distribute these files freely           //
//            so long as this notice remains present.***            //
//                                                                  //
//////////////////////////////////////////////////////////////////////

#include "h3api/H3Containers/H3String.hpp"

namespace h3
{
	_H3API_ VOID H3String::Deref()
	{
		m_string = nullptr;
		m_length = 0;
		m_capacity = 0;
	}
	_H3API_ VOID H3String::NullTerminate()
	{
		*End() = 0;
	}
	_H3API_ BOOL H3String::Realloc(UINT new_size)
	{
		return THISCALL_2(BOOL, 0x404B80, this, new_size);
	}
	_H3API_ VOID H3String::ClearUnused()
	{
		const UINT to_clear = m_capacity - m_length;
		libc::memset(PVOID(m_string + m_length), 0, to_clear);
	}
	_H3API_ BOOL H3String::CompareChars(LPCSTR chars, UINT num_chars, UINT pos, BOOL is_true) const
	{
		for (UINT i = 0; i < num_chars; ++i)
			if (m_string[pos] == chars[i])
				return is_true;

		return !is_true;
	}
	_H3API_ UINT H3String::CompareFirstOf(LPCSTR chars, UINT num_chars, BOOL is_true) const
	{
		if (Empty())
			return npos;

		for (UINT i = 0; i < m_length; ++i)
			if (CompareChars(chars, num_chars, i, is_true))
				return i;
		return npos;
	}
	_H3API_ UINT H3String::CompareLastOf(LPCSTR chars, UINT num_chars, BOOL is_true) const
	{
		if (!m_string || !m_length)
			return npos;

		for (UINT i = m_length; i > 0; --i)
			if (CompareChars(chars, num_chars, i - 1, is_true))
				return i - 1;
		return npos;
	}

	_H3API_ LPCSTR H3String::nullstring() const
	{
		return reinterpret_cast<LPCSTR>(&m_string);
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String& H3String::move(H3String&& other)
	{
		if (this == &other)
			return *this;
		Dereference();
		m_string   = other.m_string;
		m_length   = other.m_length;
		m_capacity = other.m_capacity;
		other.Deref();
		return *this;
	}
#endif

	_H3API_ H3String::H3String() :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
	}
	_H3API_ H3String::H3String(LPCSTR msg) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(msg);
	}
	_H3API_ H3String::H3String(LPCSTR msg, UINT len) :
		m_string(),
		m_length(0),
		m_capacity(0)
	{
		Assign(msg, len);
	}

	_H3API_ H3String::H3String(const H3String& other) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(other);
	}
	_H3API_ H3String::H3String(CHAR ch) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(ch);
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String::H3String(H3String&& other) noexcept :
		m_string(other.m_string),
		m_length(other.m_length),
		m_capacity(other.m_capacity)
	{
		other.Deref();
	}
#endif

	_H3API_ H3String::~H3String()
	{
		Dereference();
	}
	_H3API_ VOID H3String::Init()
	{
		THISCALL_2(VOID, 0x404130, this, 0);
	}
	_H3API_ VOID H3String::Dereference()
	{
		THISCALL_1(VOID, 0x4040F0, this);
	}
	_H3API_ BOOL H3String::Empty() const
	{
		if (m_string == nullptr || m_length == 0)
			return TRUE;
		return FALSE;
	}
	_H3API_ UINT H3String::Length() const
	{
		return m_length;
	}
	_H3API_ UINT H3String::MaxLength() const
	{
		return m_capacity;
	}
	_H3API_ LPCSTR H3String::String() const
	{
		return m_string ? m_string : nullstring();
	}
	_H3API_ CHAR* H3String::begin()
	{
		return m_string ? m_string : PCHAR(nullstring());
	}
	_H3API_ const CHAR* H3String::begin() const
	{
		return m_string ? m_string : nullstring();
	}
	_H3API_ CHAR* H3String::end()
	{
		return m_string ? m_string + m_length : PCHAR(nullstring());
	}
	_H3API_ const CHAR* H3String::end() const
	{
		return m_string ? m_string + m_length : nullstring();
	}
	_H3API_ VOID H3String::swap(H3String& other)
	{
		PCHAR s          = m_string;
		UINT l           = m_length;
		UINT c           = m_capacity;
		m_string         = other.m_string;
		m_length         = other.m_length;
		m_capacity       = other.m_capacity;
		other.m_string   = s;
		other.m_length   = l;
		other.m_capacity = c;
	}
	_H3API_ PCHAR H3String::Begin()
	{
		return m_string ? m_string : PCHAR(&m_string);
	}
	_H3API_ PCHAR H3String::End()
	{
		return m_string ? m_string + m_length : PCHAR(&m_string);
	}
	_H3API_ CHAR H3String::Last() const
	{
		if (Empty())
			return '\0';
		return m_string[m_length - 1];
	}
	_H3API_ H3String& H3String::Assign(LPCSTR mes, UINT len)
	{
		if (mes)
			return THISCALL_3(H3String&, 0x404180, this, mes, len);
		return *this;
	}
	_H3API_ H3String& H3String::Assign(LPCSTR mes)
	{
		return Assign(mes, libc::strlen(mes));
	}
	_H3API_ H3String& H3String::Assign(CHAR ch)
	{
		if (ch == '\0')
			return *this;
		return Assign(&ch, 1);
	}
	_H3API_ H3String& H3String::Assign(const H3String& other)
	{
		if (other.m_string)
			return Assign(other.String(), other.Length());
		return *this;
	}
	_H3API_ H3String& H3String::Assign(INT32 number)
	{
		char buffer[16]; // more than enough considering number can only be 12 digits [-1234567890\0]
		INT32 len = libc::sprintf(buffer, "%d", number);
		Assign(buffer, UINT(len));
		return *this;
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String& H3String::Assign(H3String&& other)
	{
		return move(std::move(other));
	}
#endif

	_H3API_ BOOL H3String::Reserve(UINT new_size)
	{
		return Realloc(new_size);
	}
	_H3API_ BOOL H3String::SetLength(UINT len)
	{
		if (len > m_capacity)
			return Realloc(len);
		m_length = len;
		NullTerminate();
		return TRUE;
	}
	_H3API_ VOID H3String::ShrinkToFit()
	{
		if (m_capacity == 0)
			return;
		UINT min_len = m_length + 2;
		if (min_len >= m_capacity)
			return;

		PCHAR tmp = CharAllocator().allocate(min_len);
		libc::memcpy(tmp, m_string - 1, min_len);
		CharAllocator().deallocate(m_string - 1);
		m_string = tmp - 1;
		m_capacity = min_len - 1;
	}
	_H3API_ H3String& H3String::Append(LPCSTR mes, UINT len)
	{
		if (mes && len)
			return THISCALL_3(H3String&, 0x41B2A0, this, mes, len);
		return *this;
	}
	_H3API_ H3String& H3String::Append(const H3String&  other)
	{
		return Append(other.String(), other.Length());
	}
	_H3API_ H3String& H3String::Append(INT32 number)
	{
		char buffer[16]; // more than enough considering number can only be 12 digits [-1234567890\0]
		const INT32 len = libc::sprintf(buffer, "%d", number);
		return Append(buffer, UINT(len));
	}
	_H3API_ H3String& H3String::Append(UINT32 number)
	{
		char buffer[16]; // more than enough considering number can only be 13 digits [0x1234567890\0]
		const UINT32 len = libc::sprintf(buffer, "0x%X", number);
		return Append(buffer, UINT(len));
	}
	_H3API_ H3String& H3String::Append(LPCSTR mes)
	{
		if (mes)
			return Append(mes, libc::strlen(mes));
		return *this;
	}
	_H3API_ H3String& H3String::Append(CHAR ch)
	{
		if (ch == '\0')
			return *this;
		return Append(&ch, 1);
	}
	_H3API_ H3String& H3String::Append(int count, CHAR ch)
	{
		return THISCALL_3(H3String&, 0x4B5CA0, this, count, ch);
	}
	_H3API_ LPCSTR H3String::FindFirst(CHAR ch)
	{
		PCHAR f = Begin();
		UINT pos = 0;
		UINT len = Length();
		while (*f && pos < len)
		{
			if (*f == ch)
				return f;
			++f;
			++pos;
		}
		return nullptr;
	}
	_H3API_ LPCSTR H3String::FindFirst(LPCSTR substr) const
	{
		if (m_string)
			return libc::strstr(String(), substr);
		return nullptr;
	}
	_H3API_ UINT H3String::FindFirstOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareFirstOf(chars, num_chars, TRUE);
	}
	_H3API_ UINT H3String::FindFirstOf(LPCSTR chars) const
	{
		return FindFirstOf(chars, libc::strlen(chars));
	}
	_H3API_ UINT H3String::FindFirstOf(const H3String& chars) const
	{
		return FindFirstOf(chars.String(), chars.Length());
	}
	_H3API_ UINT H3String::FindFirstOf(const CHAR ch) const
	{
		return CompareFirstOf(&ch, 1, TRUE);
	}
	_H3API_ UINT H3String::FindFirstNotOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareFirstOf(chars, num_chars, FALSE);
	}
	_H3API_ UINT H3String::FindFirstNotOf(LPCSTR chars) const
	{
		return FindFirstNotOf(chars, libc::strlen(chars));
	}
	_H3API_ UINT H3String::FindFirstNotOf(const H3String& chars) const
	{
		return FindFirstNotOf(chars.String(), chars.Length());
	}
	_H3API_ UINT H3String::FindFirstNotOf(const CHAR ch) const
	{
		return FindFirstNotOf(&ch, 1);
	}
	_H3API_ UINT H3String::FindLastOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareLastOf(chars, num_chars, TRUE);
	}
	_H3API_ UINT H3String::FindLastOf(LPCSTR chars) const
	{
		return CompareLastOf(chars, libc::strlen(chars), TRUE);
	}
	_H3API_ UINT H3String::FindLastOf(const H3String& chars) const
	{
		return CompareLastOf(chars.String(), chars.Length(), TRUE);
	}
	_H3API_ UINT H3String::FindLastOf(const CHAR ch) const
	{
		return CompareLastOf(&ch, 1, TRUE);
	}
	_H3API_ UINT H3String::FindLastNotOf(LPCSTR chars, UINT num_chars) const
	{
		return CompareLastOf(chars, num_chars, FALSE);
	}
	_H3API_ UINT H3String::FindLastNotOf(LPCSTR chars) const
	{
		return FindLastNotOf(chars, libc::strlen(chars));
	}
	_H3API_ UINT H3String::FindLastNotOf(const H3String& chars) const
	{
		return FindLastNotOf(chars.String(), chars.Length());
	}
	_H3API_ UINT H3String::FindLastNotOf(const CHAR ch) const
	{
		return FindLastNotOf(&ch, 1);
	}
	_H3API_ H3String& H3String::Trim()
	{
		if (Empty())
			return *this;
		constexpr CHAR whitespace[] = { ' ', '\t' };
		UINT str_start = FindFirstNotOf(whitespace, 2);
		if (str_start != npos)
			Erase(0, str_start);
		UINT str_end = FindLastNotOf(whitespace, 2);
		if (str_end != npos)
			Erase(str_end + 1, npos);
		return *this;
	}
	_H3API_ PCHAR H3String::At(UINT pos)
	{
		if (m_string)
			return m_string + std::min(pos, Length());
		return nullptr;
	}
	_H3API_ CHAR H3String::GetCharAt(UINT pos) const
	{
		if (m_string)
			return m_string[std::min(pos, Length())];
		return 0;
	}
	_H3API_ H3String& H3String::Remove(CHAR ch)
	{
		return Remove(&ch, 1);
	}
	_H3API_ H3String& H3String::Remove(LPCSTR substr)
	{
		return Remove(substr, libc::strlen(substr));
	}
	_H3API_ H3String& H3String::Remove(LPCSTR substr, UINT sublen)
	{
		PCHAR s, copy_end;
		if (!m_string)
			return *this;
		if (nullptr == (s = libc::strstr(m_string, substr)))
			return *this; // no match

		PCHAR copyFrom = s + sublen;
		while (nullptr != (copy_end = libc::strstr(copyFrom, substr)))
		{
			memmove(s, copyFrom, copy_end - copyFrom);
			s += copy_end - copyFrom;
			copyFrom = copy_end + sublen;
		}
		memmove(s, copyFrom, 1 + libc::strlen(copyFrom));
		m_length = libc::strlen(m_string);
		return *this;
	}
	_H3API_ H3String& H3String::Remove(UINT start, UINT end)
	{
		return Erase(start, end);
	}
	_H3API_ H3String & H3String::Erase(UINT pos)
	{
		return Erase(pos, pos + 1);
	}
	_H3API_ H3String & H3String::Erase(UINT first, UINT last)
	{
		if (first > m_length || first >= last)
			return *this;
		if (last > m_length)
		{
			Truncate(first);
			return *this;
		}
		PCHAR dst = begin() + first;
		PCHAR src = begin() + last;
		UINT  len = Length() - last; // copy length
		for (UINT i = 0; i < len; ++i)
			dst[i] = src[i];
		m_length -= last - first;
		m_string[m_length] = 0;
		return *this;
	}
	_H3API_ H3String & H3String::Erase(PCHAR first, PCHAR last)
	{
		return Erase(UINT(first - begin()), UINT(last - begin()));
	}
	_H3API_ BOOL H3String::Split(CHAR ch, H3String& out)
	{
		UINT pos = FindFirstOf(ch);
		if (pos == npos)
			return FALSE;
		if (pos == Length() - 1)
		{
			// split would not give anything in out
			Truncate(pos);
			return TRUE;
		}

		out.Assign(begin() + pos + 1, Length() - pos - 1);
		Truncate(pos);
		return TRUE;
	}
	_H3API_ VOID H3String::Erase()
	{
		libc::memset(Begin(), 0, Length());
		m_length = 0;
	}
	_H3API_ BOOL H3String::Equals(LPCSTR msg, UINT len) const
	{
		if (!msg || Length() != len)
			return FALSE;

		return memcmp(msg, String(), Length()) == 0;
	}
	_H3API_ BOOL H3String::Equals(LPCSTR msg) const
	{
		if (!msg)
			return npos;
		return Equals(msg, libc::strlen(msg));
	}
	_H3API_ BOOL H3String::Equals(const H3String& other) const
	{
		return Equals(other.String(), other.Length());
	}
	_H3API_ BOOL H3String::Equals_i(LPCSTR msg, UINT len) const
	{
		if (Length() != len)
			return FALSE;
		return (libc::strcmpi(msg, String()) == 0);
	}
	_H3API_ BOOL H3String::Equals_i(LPCSTR msg) const
	{
		if (!msg)
			return FALSE;
		return Equals_i(msg, libc::strlen(msg));
	}
	_H3API_ BOOL H3String::Equals_i(const H3String& other) const
	{
		return Equals_i(other.String(), other.Length());
	}
	_H3API_ H3String& H3String::Insert(UINT pos, LPCSTR msg, UINT len)
	{
		if (len == 0 || msg == nullptr)
			return *this;
		if (pos >= Length()) // trying to insert at or after end
			return Append(msg, len);
		if (!Reserve(Length() + len))
			return *this;
		UINT copylen = Length() - pos;
		H3String temp; // simpler than malloc + free
		temp.Assign(m_string + pos, copylen);
		Truncate(pos); // temporarily cut out
		Append(msg, len); // insert msg
		Append(temp); // insert original end

		return *this;
	}
	_H3API_ H3String& H3String::Insert(UINT pos, LPCSTR msg)
	{
		if (msg)
			return Insert(pos, msg, libc::strlen(msg));
		return *this;
	}
	_H3API_ H3String& H3String::Insert(UINT pos, const H3String& to_insert)
	{
		return Insert(pos, to_insert.String(), to_insert.Length());
	}
	_H3API_ H3String& H3String::Insert(UINT pos, CHAR ch)
	{
		return Insert(pos, &ch, 1);
	}
	_H3API_ INT H3String::Compare(LPCSTR other) const
	{
		return libc::strcmp(String(), other);
	}
	_H3API_ INT H3String::Compare(const H3String & other) const
	{
		return Compare(other.String());
	}
	_H3API_ INT H3String::Comparei(LPCSTR other) const
	{
		return libc::strcmpi(String(), other);
	}
	_H3API_ INT H3String::Comparei(const H3String & other) const
	{
		return libc::strcmpi(String(), other.String());
	}
	_H3API_ BOOL H3String::operator<(const H3String& other) const
	{
		return libc::strcmp(String(), other.String()) < 0;
	}
	_H3API_ BOOL H3String::Truncate(UINT position)
	{
		if (position == npos)
			return FALSE;
		if (position < Length() && m_string)
		{
			m_length = position;
			m_string[m_length] = 0;
			return TRUE;
		}
		return FALSE;
	}
	_H3API_ UINT H3String::Occurrences(CHAR ch) const
	{
		if (Empty())
			return 0;
		UINT n = 0;
		for (UINT i = 0; i < m_length; ++i)
			if (m_string[i] == ch)
				++n;
		return n;
	}
	_H3API_ H3String& H3String::operator=(const H3String& other)
	{
		return Assign(other);
	}
	_H3API_ H3String& H3String::operator=(LPCSTR msg)
	{
		return Assign(msg);
	}
	_H3API_ H3String& H3String::operator=(CHAR ch)
	{
		return Assign(ch);
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3String& H3String::operator=(H3String&& other) noexcept
	{
		if (&other == this)
			return *this;

		m_string   = other.m_string;
		m_length   = other.m_length;
		m_capacity = other.m_capacity;
		other.Deref();

		return *this;
	}
#endif

	_H3API_ H3String& H3String::operator+=(const H3String& other)
	{
		return Append(other);
	}
	_H3API_ H3String& H3String::operator+=(LPCSTR msg)
	{
		return Append(msg);
	}
	_H3API_ H3String& H3String::operator+=(CHAR ch)
	{
		return Append(ch);
	}
	_H3API_ H3String& H3String::operator+=(const INT32 number)
	{
		return Append(number);
	}
	_H3API_ H3String& H3String::operator+=(UINT32 number)
	{
		return Append(number);
	}
	_H3API_ H3WString H3String::ToH3WString(UINT code_page) const
	{
		// MultiByteToWideChar
		//UINT req_len = STDCALL_6(UINT, PtrAt(0x63A1CC), code_page, 0, m_string, -1, 0, 0);
		UINT req_len = libc::MultiByteToWideChar(code_page, 0, m_string, -1, 0, 0);
		H3WString wstring;
		wstring.Reserve(req_len);

		// MultiByteToWideChar
		//STDCALL_6(UINT, PtrAt(0x63A1CC), code_page, 0, m_string, -1, wstring.String(), req_len);
		libc::MultiByteToWideChar( code_page, 0, m_string, -1, wstring.Begin(), req_len);
		wstring.m_length = req_len - 1; // wstring is null-terminated by MultiByteToWideChar
		return wstring;
	}
	_H3API_ BOOL H3String::operator==(const H3String& h3str) const
	{
		return Compare(h3str.String()) == 0;
	}
	_H3API_ BOOL H3String::operator==(LPCSTR str) const
	{
		return Compare(str) == 0;
	}
	_H3API_ BOOL H3String::operator!=(const H3String& h3str) const
	{
		return Compare(h3str.String()) != 0;
	}
	_H3API_ BOOL H3String::operator!=(LPCSTR str) const
	{
		return Compare(str) != 0;
	}
	_H3API_ CHAR H3String::operator[](UINT32 pos) const
	{
		return m_string[pos];
	}
	_H3API_ CHAR& H3String::operator[](UINT32 pos)
	{
		return m_string[pos];
	}
	_H3API_ INT8 H3String::References() const
	{
		if (m_string)
			return m_string[-1];
		return 0;
	}
	_H3API_ VOID H3String::IncreaseReferences()
	{
		if (m_string)
			++m_string[-1];
	}
	_H3API_ BOOL H3String::FormattedNumber(INT32 number)
	{
		if (!m_string && !Reserve())
			return FALSE;
		m_length = H3Numbers::AddCommas(number, m_string);

		return TRUE;
	}
	_H3API_ BOOL H3String::ScaledNumber(INT32 number, INT32 decimals)
	{
		if (!m_string && !Reserve())
			return FALSE;
		m_length = H3Numbers::MakeReadable(number, m_string, decimals);
		return TRUE;
	}
	_H3API_ H3String H3String::PrintfH3(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		CDECL_3(void, 0x6190DE, 0x69971C, format, args);
		va_end(args);
		return H3String(PCHAR(0x69971C));
	}
	_H3API_ H3String & H3String::PrintfAppendH3(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		CDECL_3(void, 0x6190DE, 0x69971C, format, args);
		va_end(args);
		return Append(PCHAR(0x69971C));
	}
	_H3API_ INT32 H3String::ToSigned() const
	{
		return libc::atoi(String());
	}
	_H3API_ UINT32 H3String::ToUnsigned() const
	{
		return libc::atol(String());
	}
	_H3API_ DOUBLE H3String::ToDouble() const
	{
		return libc::atof(String());
	}
	_H3API_ INT32 H3String::HexToSigned() const
	{
		return libc::strtol(String(), nullptr, 16);
	}
	_H3API_ UINT32 H3String::HexToUnsigned() const
	{
		return libc::strtoul(String(), nullptr, 16);
	}
	_H3API_ H3String H3String::GetLocalTime()
	{
		SYSTEMTIME time;
		STDCALL_1(VOID, PtrAt(0x63A248), &time);
		H3String str;
		str.Printf("%04d.%02d.%02d - %02dh%02dm%02ds",
			time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		return str;
	}
	_H3API_ H3String H3String::FormatNumber(INT32 number)
	{
		H3String str;
		// longest possible is -1,234,567,890 (14)
		str.Reserve(15);
		CHAR buffer[16];
		INT32 num_len = libc::sprintf(buffer, "%d", number);
		INT32 len = num_len;
		PCHAR dst = str.Begin();
		PCHAR src = buffer;
		if (*src == '-')
		{
			*dst++ = *src++;
			--num_len;
		}
		for (INT32 commas = 2 - num_len % 3; *src; commas = (commas + 1) % 3)
		{
			*dst++ = *src++;
			if (commas == 1)
				*dst++ = ',';
		}
		*--dst = 0;
		str.m_length = dst - str.m_string;
		return str;
	}
	_H3API_ H3String H3String::ShortScale(INT32 num, INT32 decimals)
	{
		constexpr INT32 RN_MIN_VALUE = 10000;
		INT32 power;
		char buffer[16];
		H3String str;

		// * work with positives
		INT64 m;
		if (num != INT_MIN)
			m = Abs(num);
		else
			m = INT64(INT_MAX) + 1;

		if (m < RN_MIN_VALUE)
		{
			str.Append(num);
			return str;
		}

		// * round the number to required precision
		INT32 dec  = std::min(decimals, 3);
		INT32 plus = 500;
		INT32 div  = 1000;
		for (INT32 i = 0; i < dec; i++)
		{
			plus /= 10;
			div  /= 10;
		}
		INT32 d = power = 0;
		while (m >= 1000)
		{
			d  = INT32(m);
			m /= 1000;
			power++;
		}
		// * rounding, same idea as f = round(f + 0.5)
		d = (d + plus) / div * div;

		// * print template
		INT32 len = libc::sprintf(buffer, "%d", d);
		INT32 c = 2 - len % 3;
		str.Reserve(15);
		CHAR *dst = str.m_string;
		CHAR *src = buffer;

		// * leading negative
		if (num < 0)
			*dst++ = '-';

		// * copy source to destination
		while (*src)
		{
			*dst++ = *src++;
			if (c == 1)
			{
				// * if decimals are required
				if (dec)
				{
					*dst++ = '.';
					// * add required precision
					for (INT32 i = 0; i < dec; i++)
						*dst++ = *src++;
				}
				break;
			}
			c = (c + 1) % 3;
		}
		// * add proper ending
		constexpr CHAR scale[] = { 0, 'k', 'M', 'B' };
		*dst++ = scale[power];
		*dst = 0;

		str.m_length = dst - str.m_string - (power == 0);

		return str;
	}
	_H3API_ H3String H3String::Format(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		H3String str = Format(format, args);
		va_end(args);
		return str;
	}
	_H3API_ H3String H3String::Format(LPCSTR format, va_list args)
	{
		H3String str;
		INT32 len = _vsnprintf(nullptr, 0, format, args);
		if (len > 0 && str.Reserve(len + 1))
		{
			len = libc::vsprintf(str.Begin(), format, args);
			str.m_length = len;
		}
		return str;
	}

	_H3API_ H3String& H3String::Printf(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		Assign(Format(format, args));
		va_end(args);
		return *this;
	}
	_H3API_ H3String& H3String::PrintfAppend(LPCSTR format, ...)
	{
		va_list args;
		va_start(args, format);
		Append(Format(format, args));
		va_end(args);
		return *this;
	}

#ifdef _H3API_STD_CONVERSIONS_
	_H3API_ H3String::H3String(const std::string& str) :
		m_string(nullptr),
		m_length(0),
		m_capacity(0)
	{
		Assign(str);
	}
	_H3API_ INT H3String::operator==(const std::string& str) const
	{
		return Compare(str.c_str());
	}
	_H3API_ H3String& H3String::operator+=(const std::string& str)
	{
		return Append(str);
	}
	_H3API_ H3String& H3String::operator=(const std::string& str)
	{
		return Assign(str);
	}
	_H3API_ H3String& H3String::Assign(const std::string& str)
	{
		return Assign(str.c_str(), str.length());
	}
	_H3API_ H3String& H3String::Append(const std::string& str)
	{
		Append(str.c_str(), str.length());
		return *this;
	}
	_H3API_ std::string H3String::to_std_string() const
	{
		return std::string(String(), Length());
	}
#endif /* _H3API_STD_CONVERSIONS_ */

	_H3API_ VOID H3WString::Destroy()
	{
		if (m_string)
		{
			ByteAllocator().destroy(base());
			deref();
		}
	}
	_H3API_ VOID H3WString::tidy(BOOL8 dereference /*= TRUE*/)
	{
		THISCALL_2(VOID, 0x612988, this, dereference);
	}
	_H3API_ VOID H3WString::deref()
	{
		m_string = nullptr;
		m_length = 0;
		m_capacity = 0;
	}
	_H3API_ BOOL8 H3WString::grow(UINT32 size, BOOL8 trim /*= FALSE*/)
	{
		return THISCALL_3(BOOL8, 0x6128FF, this, size, trim);
	}
	_H3API_ UINT8& H3WString::references()
	{
		return *(reinterpret_cast<PUINT8>(m_string) - 1);
	}
	_H3API_ PBYTE H3WString::base()
	{
		return m_string ? PBYTE(PBYTE(m_string) - 2) : nullptr;
	}

#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3WString& H3WString::move(H3WString&& other)
	{
		if (this == &other)
			return *this;
		tidy(TRUE);
		m_string   = other.m_string;
		m_length   = other.m_length;
		m_capacity = other.m_capacity;
		other.deref();
		return *this;
	}
#endif

	_H3API_ H3WString::H3WString() :
		m_string(), m_length(), m_capacity()
	{
	}
	_H3API_ H3WString::H3WString(const H3WString& other) :
		m_string(), m_length(), m_capacity()
	{
		Assign(other);
	}
	_H3API_ H3WString::H3WString(LPCWSTR text) :
		m_string(), m_length(), m_capacity()
	{
		Assign(text);
	}
	_H3API_ H3WString::H3WString(WCHAR character) :
		m_string(), m_length(), m_capacity()
	{
		Assign(character);
	}
	_H3API_ H3WString::H3WString(LPCWSTR text, UINT32 length)
	{
		Assign(text, length);
	}
	_H3API_ H3WString::~H3WString()
	{
		tidy(TRUE);
	}
	_H3API_ H3WString& H3WString::Append(LPCWSTR text, UINT32 length)
	{
		if (length == 0)
			return *this;
		const UINT size = m_length + length;
		if (size >= max_len)
			STDCALL_0(VOID, 0x60B0FB); // string too long exception

		if (size >= m_capacity && !grow(size))
			return *this;

		WCHAR* dst = m_string + m_length;
		LPCWSTR src = text;
		const UINT extra_length = length;
		while (length > 0)
		{
			*dst++ = *src++;
			--length;
		}
		*dst = 0;
		m_length += extra_length;

		return *this;
	}
	_H3API_ H3WString& H3WString::Append(LPCWSTR text)
	{
		return Append(text, libc::wcslen(text));
	}
	_H3API_ H3WString& H3WString::Append(WCHAR character)
	{
		return Append(&character, 1);
	}
	_H3API_ H3WString& H3WString::Append(const H3WString& other)
	{
		return Append(other, 0, other.Length());
	}
	_H3API_ H3WString& H3WString::Append(const H3WString& other, UINT32 start_position, UINT32 end_position)
	{
		return THISCALL_4(H3WString&, 0x612B0C, this, other, start_position, end_position);
	}
#ifdef _H3API_CPLUSPLUS11_
	_H3API_ H3WString& H3WString::Assign(H3WString&& other)
	{
		return move(std::move(other));
	}
#endif

	_H3API_ H3WString& H3WString::Assign(LPCWSTR text, UINT32 length)
	{
		return THISCALL_3(H3WString&, 0x6126F3, this, text, length);
	}
	_H3API_ H3WString& H3WString::Assign(LPCWSTR text)
	{
		return Assign(text, libc::wcslen(text));
	}
	_H3API_ H3WString& H3WString::Assign(const H3WString& other)
	{
		return Assign(other.String(), other.Length());
	}
	_H3API_ H3WString& H3WString::SoftCopy(const H3WString& other)
	{
		return THISCALL_4(H3WString&, 0x612615, this, &other, 0, other.Length());
	}
	_H3API_ H3WString& H3WString::Assign(WCHAR character)
	{
		return Assign(&character, 1);
	}
	_H3API_ UINT32 H3WString::Size() const
	{
		return m_length;
	}
	_H3API_ UINT32 H3WString::Length() const
	{
		return m_length;
	}
	_H3API_ BOOL32 H3WString::IsEmpty() const
	{
		return m_length == 0;
	}
	_H3API_ LPCWSTR H3WString::String() const
	{
		return m_string ? m_string : reinterpret_cast<LPCWSTR>(&m_string);
	}
	_H3API_ VOID H3WString::Insert(UINT32 start_position, UINT32 end_position, WCHAR character)
	{
		THISCALL_4(VOID, 0x61278D, this, start_position, end_position, character);
	}
	_H3API_ H3WString& H3WString::Insert(UINT32 start_position, LPCWSTR text)
	{
		return Insert(start_position, libc::wcslen(text));
	}
	_H3API_ H3WString& H3WString::Insert(UINT32 start_position, LPCWSTR text, UINT length)
	{
		if (length == 0 || text == nullptr)
			return *this;
		// * trying to insert at or after end
		if (start_position >= Length())
			return Append(text, length);

		if (!Reserve(Length() + length))
			return *this;

		UINT copylen = Length() - start_position;
		// * simpler than malloc + free
		H3WString temp;
		temp.Assign(m_string + start_position, copylen);
		// * temporarily cut end out at starting position
		m_string[start_position] = WCHAR(0);
		m_length = start_position;
		// * insert msg
		Append(text, length);
		// * insert original end
		Append(temp);
		return *this;
	}
	_H3API_ H3WString& H3WString::Insert(UINT32 start_position, WCHAR text)
	{
		return Insert(start_position, &text, 1);
	}
	_H3API_ H3WString& H3WString::Insert(UINT32 start_position, const H3WString& other)
	{
		return Insert(start_position, other.String(), other.Length());
	}
	_H3API_ PWCHAR H3WString::Begin()
	{
		return m_string ? m_string : PWCHAR(&m_string);
	}
	_H3API_ LPCWSTR H3WString::begin()
	{
		return m_string ? m_string : PWCHAR(&m_string);
	}
	_H3API_ LPCWSTR H3WString::begin() const
	{
		return m_string ? m_string : PWCHAR(&m_string);
	}
	_H3API_ LPCWSTR H3WString::end()
	{
		return m_string ? m_string + m_length : PWCHAR(&m_string);
	}
	_H3API_ LPCWSTR H3WString::end() const
	{
		return m_string ? m_string + m_length : PWCHAR(&m_string);
	}
	_H3API_ BOOL8 H3WString::Reserve(UINT32 length)
	{
		return grow(length);
	}
	_H3API_ UINT8 H3WString::References() const
	{
		return *(reinterpret_cast<PUINT8>(m_string) - 1);
	}
	_H3API_ VOID H3WString::IncreaseReferences()
	{
		UINT8& ref = references();
		if (ref != frozen)
			++ref;
	}
	_H3API_ VOID H3WString::DecreaseReferences()
	{
		UINT8& ref = references();
		if (ref && ref != frozen)
			--ref;
	}
	_H3API_ H3WString& H3WString::Erase(UINT32 start_position, UINT32 end_position)
	{
		return THISCALL_3(H3WString&, 0x612867, this, start_position, end_position);
	}
	_H3API_ H3WString& H3WString::Erase()
	{
		return Erase(0, npos);
	}
	_H3API_ INT32 H3WString::Compare(LPCWSTR string, UINT32 length) const
	{
		// * normalize to usual -1, 0 or 1 result to indicate <, = or >
		return libc::CompareStringW(LOCALE_NEUTRAL, 0, String(), Length(), string, length) - CSTR_EQUAL;
	}
	_H3API_ INT32 H3WString::Compare(LPCWSTR string) const
	{
		return Compare(string, libc::wcslen(string));
	}
	_H3API_ INT32 H3WString::Compare(const H3WString& other) const
	{
		return Compare(other.String(), other.Length());
	}
	_H3API_ INT32 H3WString::Compare(WCHAR character) const
	{
		return Compare(&character, 1);
	}
	_H3API_ BOOL H3WString::Equals(LPCWSTR string, UINT32 length) const
	{
		if (Length() != length)
			return FALSE;
		return Compare(string, length) == 0;
	}
	_H3API_ BOOL H3WString::Equals(LPCWSTR string) const
	{
		return Equals(string, libc::wcslen(string));
	}
	_H3API_ BOOL H3WString::Equals(const H3WString& other) const
	{
		return Equals(other.String(), other.Length());
	}
	_H3API_ BOOL H3WString::Equals(WCHAR character) const
	{
		return Equals(&character, 1);
	}
	_H3API_ WCHAR H3WString::operator[](UINT position) const
	{
		return m_string[position];
	}
	_H3API_ WCHAR& H3WString::operator[](UINT position)
	{
		return m_string[position];
	}
	_H3API_ BOOL H3WString::operator==(const H3WString& other)
	{
		return Equals(other);
	}
	_H3API_ BOOL H3WString::operator==(LPCWSTR msg)
	{
		return Equals(msg);
	}
	_H3API_ BOOL H3WString::operator==(WCHAR ch)
	{
		return Equals(ch);
	}
	_H3API_ H3WString& H3WString::operator+=(WCHAR ch)
	{
		return Append(ch);
	}
	_H3API_ H3WString& H3WString::operator+=(LPCWSTR msg)
	{
		return Append(msg);
	}
	_H3API_ H3WString& H3WString::operator+=(const H3WString& other)
	{
		return Append(other);
	}
	_H3API_ H3String H3WString::ToH3String(UINT code_page) const
	{
		// WideCharToMultiByte
		//UINT req_len = STDCALL_8(UINT, PtrAt(0x63A1C4), code_page, 0, m_string, -1, NULL, 0, NULL, NULL);
		UINT req_len = libc::WideCharToMultiByte(code_page, 0, m_string, -1, NULL, 0, NULL, NULL);
		H3String string;
		string.Reserve(req_len);

		// WideCharToMultiByte
		//STDCALL_8(UINT, PtrAt(0x63A1C4), code_page, 0, m_string, -1, string.String(), req_len, NULL, NULL);
		libc::WideCharToMultiByte(code_page, 0, m_string, -1, string.Begin(), req_len, NULL, NULL);
		string.m_length = req_len - 1; // string is null-terminated by WideCharToMultiByte
		return string;
	}
	_H3API_ H3WString& H3WString::operator=(WCHAR ch)
	{
		return Assign(ch);
	}
	_H3API_ H3WString& H3WString::operator=(LPCWSTR msg)
	{
		return Assign(msg);
	}
	_H3API_ H3WString& H3WString::operator=(const H3WString& other)
	{
		return Assign(other);
	}
}