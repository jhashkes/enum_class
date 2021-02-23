// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2021 Jonathan Hashkes <jon_repo@hashkes.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>

namespace enum_class
{
	template<typename EnumValue>
	using NameValueVec = std::vector<std::pair<std::string, EnumValue>>;

	template<typename EnumValue>
	using ValueToNameMap = std::unordered_map<EnumValue, std::string>;

	template<typename EnumValue>
	using NameToValueMap = std::unordered_map<std::string, EnumValue>;

	template<typename EnumValue>
	class EnumInfo
	{
	protected:
		static bool Init(std::string init_str)
		{
			name_value_vec_.clear();
			value_to_name_map_.clear();
			name_to_value_map_.clear();

			std::istringstream ss(init_str);
			typename std::underlying_type<EnumValue>::type base_value = 0;
			while (ss.good())
			{
				std::string enum_def;
				std::getline(ss, enum_def, ',');
				std::istringstream token_ss(enum_def);
				std::string name;
				token_ss >> name;
				if (token_ss.good())
				{
					std::string eq_sign;
					token_ss >> eq_sign >> base_value;
				}
				EnumValue value = static_cast<EnumValue>(base_value++);
				name_value_vec_.emplace_back(name, value);
				value_to_name_map_.emplace(value, name);
				name_to_value_map_.emplace(name, value);
			}
			return true;
		}

	public:
		static inline std::string Name(EnumValue value)
		{
			const auto& value_to_name_map = EnumInfo<EnumValue>::value_to_name_map_;
			auto it = value_to_name_map.find(value);
			if (it == value_to_name_map.end())
				return "N/A";
			return it->second;
		}

		static inline std::optional<EnumValue> Value(std::string name)
		{
			const auto& name_to_value_map = EnumInfo<EnumValue>::name_to_value_map_;
			auto it = name_to_value_map.find(name);
			if (it == name_to_value_map.end())
				return {};
			return it->second;
		}

		static inline std::vector<std::string> Names()
		{
			const auto& name_value_vec = EnumInfo<EnumValue>::name_value_vec_;
			std::vector<std::string> values;
			values.reserve(name_value_vec.size());
			for (const auto& [name, value] : name_value_vec)
				values.emplace_back(name);
			return values;
		}

		static inline std::vector<EnumValue> Values()
		{
			const auto& name_value_vec = EnumInfo<EnumValue>::name_value_vec_;
			std::vector<EnumValue> values;
			values.reserve(name_value_vec.size());
			for (const auto& [name, value] : name_value_vec)
				values.emplace_back(value);
			return values;
		}

	private:
		static inline NameValueVec<EnumValue> name_value_vec_;
		static inline ValueToNameMap<EnumValue> value_to_name_map_;
		static inline NameToValueMap<EnumValue> name_to_value_map_;
	};

	template<typename EnumValue>
	static inline std::string Name(EnumValue value)
	{
		return EnumInfo<EnumValue>::Name(value);
	}

	template<typename EnumValue>
	static inline std::optional<EnumValue> Value(std::string name)
	{
		return EnumInfo<EnumValue>::Value(name);
	}

	template<typename EnumValue>
	static inline std::vector<std::string> Names()
	{
		return EnumInfo<EnumValue>::Names();
	}

	template<typename EnumValue>
	static inline std::vector<EnumValue> Values()
	{
		return EnumInfo<EnumValue>::Values();
	}
}

#define ENUM_CLASS(ENUMTYPE, BASETYPE, ...) \
	enum class ENUMTYPE : BASETYPE { __VA_ARGS__ }; \
	struct ENUMTYPE##Meta : enum_class::EnumInfo<ENUMTYPE> { inline static const bool dummy_ = Init(#__VA_ARGS__); }


