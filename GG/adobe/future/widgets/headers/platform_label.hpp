/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/


#ifndef ADOBE_LABEL_T_HPP
#define ADOBE_LABEL_T_HPP

#include <string>

#include <boost/noncopyable.hpp>

#include <GG/Clr.h>
#include <GG/FontFwd.h>

#include <GG/adobe/memory.hpp>
#include <GG/adobe/layout_attributes.hpp>
#include <GG/adobe/widget_attributes.hpp>
#include <GG/adobe/future/widgets/headers/widget_utils.hpp>


namespace GG {
    class TextControl;
    class Wnd;
}

namespace adobe {
    struct label_t  : boost::noncopyable
    {
        label_t(const std::string&        name, 
                const std::string&        alt_text, 
                std::size_t               characters,
                GG::Flags<GG::TextFormat> format,
                GG::Clr                   color);

        GG::TextControl*          window_m;
        GG::Flags<GG::TextFormat> format_m;
        GG::Clr                   color_m;
        std::string               name_m;
        std::string               alt_text_m;
        std::size_t               characters_m;

        implementation::color_proxy_t color_proxy_m;
    };

    void measure(label_t& value, extents_t& result);

    void measure_vertical(label_t& value, extents_t& calculated_horizontal, 
                          const place_data_t& placed_horizontal);

    void place(label_t& value, const place_data_t& place_data);

    void enable(label_t& value, bool make_enabled);

    extents_t measure_text(const std::string& text, const boost::shared_ptr<GG::Font>& font);

    std::string get_control_string(const label_t& widget);

    inline GG::TextControl* get_display(label_t& widget)
    { return widget.window_m; }

} // namespace adobe


#endif

/****************************************************************************************************/
