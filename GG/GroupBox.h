// -*- C++ -*-
/* GG is a GUI for SDL and OpenGL.
   Copyright (C) 2003-2008 T. Zachary Laine

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1
   of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
    
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA

   If you do not wish to comply with the terms of the LGPL please
   contact the author as other terms are available for a fee.
    
   Zach Laine
   whatwasthataddress@gmail.com */

/** \file GroupBox.h \brief Contains the GroupBox class, a simple,
    noninteractive box with an optional label. */

#ifndef _GG_GroupBox_h_
#define _GG_GroupBox_h_

#include <GG/ClrConstants.h>
#include <GG/Wnd.h>


namespace GG {

class Font;
class TextControl;

/** \brief This is a noninteractive box with an optional label. */
class GG_API GroupBox : public Wnd
{
public:
    /** \name Structors */ ///@{
    /** Ctor. Height is determined from the font and point size used. */
    GroupBox(X x, Y y, X w, Y h, const std::string& label, const boost::shared_ptr<Font>& font, Clr color,
             Clr text_color = CLR_BLACK, Clr interior = CLR_ZERO, Flags<WndFlag> flags = Flags<WndFlag>());
    //@}

    /** \name Accessors */ ///@{
    virtual Pt ClientUpperLeft() const;
    virtual Pt ClientLowerRight() const;
    //@}

    /** \name Mutators */ ///@{
    virtual void Render();

    /** Sets the color of the group box. */
    void SetColor(Clr c);

    /** Sets the color of the label's text. */
    void SetTextColor(Clr c);

    /** Sets the interior color of the box. */
    void SetInteriorColor(Clr c);

    virtual void SetText(const std::string& str);
    //@}

protected:
    /** \name Structors */ ///@{
    GroupBox(); ///< Default ctor.
    //@}

    /** The thickness with which to render the frame. */
    static const int FRAME_THICK;

    /** The number of pixels to leave between the client area and the
        frame. */
    static const int PIXEL_MARGIN;

private:
    Clr                     m_color;      ///< Color of box frame
    Clr                     m_text_color; ///< Color of label text
    Clr                     m_int_color;  ///< Color of background inside box
    boost::shared_ptr<Font> m_font;
    TextControl*            m_label;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

} // namespace GG

// template implementations
template <class Archive>
void GG::GroupBox::serialize(Archive& ar, const unsigned int version)
{
    ar  & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Wnd)
        & BOOST_SERIALIZATION_NVP(m_color)
        & BOOST_SERIALIZATION_NVP(m_text_color)
        & BOOST_SERIALIZATION_NVP(m_int_color)
        & BOOST_SERIALIZATION_NVP(m_label);
}

#endif // _GG_GroupBox_h_
