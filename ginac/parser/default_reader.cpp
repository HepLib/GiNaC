/** @file default_reader.cpp
 *
 *  Implementation of the default and builtin readers (part of GiNaC's parser).
 **/

/*
 *  GiNaC Copyright (C) 1999-2023 Johannes Gutenberg University Mainz, Germany
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "parse_context.h"
#include "power.h"
#include "lst.h"
#include "operators.h"
#include "inifcns.h"

#include <cstdint> // for uintptr_t

namespace GiNaC
{

static ex sqrt_reader(const exvector& ev)
{
	return GiNaC::sqrt(ev[0]);
}

static ex pow_reader(const exvector& ev)
{
	return GiNaC::pow(ev[0], ev[1]);
}

static ex power_reader(const exvector& ev)
{
	return GiNaC::power(ev[0], ev[1]);
}

static ex lst_reader(const exvector& ev)
{
	return GiNaC::lst(ev.begin(), ev.end());
}


// function::registered_functions() is protected, but we need to access it
// TODO: add a proper const method to the `function' class, so we don't
// need this silly hack any more.
class registered_functions_hack : public function
{
public:
	static const std::vector<function_options>& get_registered_functions()
	{
		return function::registered_functions();
	}
private:
	registered_functions_hack();
	registered_functions_hack(const registered_functions_hack&);
	registered_functions_hack& operator=(const registered_functions_hack&);
};


const prototype_table& get_default_reader()
{
	using std::make_pair;
	static bool initialized = false;
	static prototype_table reader;
	if (!initialized) {
		
		reader.insert({{"sqrt", 1}, reader_func(sqrt_reader)});
        reader.insert({{"pow", 2}, reader_func(pow_reader)});
        reader.insert({{"power", 2}, reader_func(power_reader)});
        reader.insert({{"lst", 0}, reader_func(lst_reader)});
		unsigned serial = 0;
		for (auto & it : registered_functions_hack::get_registered_functions()) {
			prototype proto = make_pair(it.get_name(), it.get_nparams());
			reader.insert({{it.get_name(), it.get_nparams()}, reader_func(serial)});
			++serial;
		}
		initialized = true;
	}
	return reader;
}

const prototype_table& get_builtin_reader()
{
	using std::make_pair;
	static bool initialized = false;
	static prototype_table reader;
	if (!initialized) {
		
		reader.insert({{"sqrt", 1}, reader_func(sqrt_reader)});
        reader.insert({{"pow", 2}, reader_func(pow_reader)});
        reader.insert({{"power", 2}, reader_func(power_reader)});
        reader.insert({{"lst", 0}, reader_func(lst_reader)});
		enum {
			log,
			exp,
			sin,
			cos,
			tan,
			asin,
			acos,
			atan,
			sinh,
			cosh,
			tanh,
			asinh,
			acosh,
			atanh,
			atan2,
			Li2,
			Li3,
			zetaderiv,
			Li,
			S,
			H,
			lgamma,
			tgamma,
			beta,
			factorial,
			binomial,
			Order,
			NFUNCTIONS
		};
		auto it = registered_functions_hack::get_registered_functions().begin();
		unsigned serial = 0;
		for ( ; serial<NFUNCTIONS; ++it, ++serial ) {
			prototype proto = make_pair(it->get_name(), it->get_nparams());
			reader.insert({{it->get_name(), it->get_nparams()}, reader_func(serial)});
		}
		initialized = true;
	}
	return reader;
}

} // namespace GiNaC
