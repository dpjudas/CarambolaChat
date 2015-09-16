/*
**  ClanLib SDK
**  Copyright (c) 1997-2015 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/


#pragma once

#include "dom_node.h"

/// \brief DOM Notation class.
class DomNotation : public DomNode
{
public:
	/// \brief Constructs a DOM Notation handle.
	DomNotation();

	/// \brief Constructs a DomNotation
	///
	/// \param impl = Shared Ptr
	DomNotation(const std::shared_ptr<DomNode_Impl> &impl);

	~DomNotation();

	/// \brief The public identifier of this notation.
	/** <p>If the public identifier was not specified, this is null.</p>*/
	DomString get_public_id() const;

	/// \brief The system identifier of this notation.
	/** <p>If the system identifier was not specified, this is null.</p>*/
	DomString get_system_id() const;
};
