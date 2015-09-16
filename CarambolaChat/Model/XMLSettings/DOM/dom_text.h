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

#include "dom_character_data.h"

/// \brief DOM Text class.
class DomText : public DomCharacterData
{
public:
	/// \brief Constructs a DOM Text handle.
	DomText();

	/// \brief Constructs a DomText
	///
	/// \param doc = Dom Document
	/// \param data = Dom String
	DomText(DomDocument &doc, const DomString &data);

	/// \brief Constructs a DomText
	///
	/// \param impl = Shared Ptr
	DomText(const std::shared_ptr<DomNode_Impl> &impl);

	~DomText();

	/// \brief Breaks this Text node into two Text nodes at the specified offset, keeping both in the tree as siblings.
	/** <p>node then only contains all the content up to the offset point. And a new Text node, which
		is inserted as the next sibling of this node, contains all the content at and after the offset
		point.</p>
		\param offset The offset at which to split.
		retval: The new Text node.*/
	DomText split_text(unsigned long offset);

protected:
	/// \brief Constructs a DomText
	///
	/// \param doc = Dom Document
	/// \param node_type = short
	DomText(DomDocument &doc, unsigned short node_type);
};
