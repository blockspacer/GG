/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/

/****************************************************************************************************/

#ifndef ADOBE_SLIDER_HPP
#define ADOBE_SLIDER_HPP

/****************************************************************************************************/

#include <GG/adobe/config.hpp>

#include <GG/Base.h>
#include <GG/Clr.h>
#include <GG/adobe/extents.hpp>
#include <GG/adobe/layout_attributes.hpp>
#include <GG/adobe/widget_attributes.hpp>
#include <GG/adobe/future/widgets/headers/slider_helper.hpp>
#include <GG/adobe/future/widgets/headers/widget_utils.hpp>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <string>


namespace GG {
    template <typename T>
    class Slider;
}

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

struct slider_t : boost::noncopyable
{
    typedef double                                    model_type;
    typedef boost::function<void (const model_type&)> setter_type;

    slider_t(const std::string&          alt_text,
             bool                        is_vertical,
             std::size_t                 num_ticks,
             const value_range_format_t& format,
             int                         length,
             GG::Clr                     color,
             int                         tab_width,
             int                         tab_length,
             int                         line_width,
             GG::SliderLineStyle         line_style,
             name_t                      signal_id);

    void measure(extents_t& result);

    void place(const place_data_t& place_data);

    void display(const model_type& item);

    void enable(bool make_enabled);

    void monitor(const setter_type& proc);

    GG::Slider<double>*  control_m;
    std::string          alt_text_m;
    bool                 is_vertical_m;
    std::size_t          num_ticks_m;
    value_range_format_t format_m;
    int                  length_m;
    GG::Clr              color_m;
    int                  tab_width_m;
    int                  tab_length_m;
    int                  line_width_m;
    GG::SliderLineStyle  line_style_m;
    name_t               signal_id_m;
    setter_type          value_proc_m;
    model_type           last_m; // Used to debounce
    model_type           value_m;

    boost::function<void (int, int, int)> slid_proc_m;
    boost::function<void (int, int, int)> slid_and_stopped_proc_m;

    implementation::color_proxy_t color_proxy_m;
};

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/

#endif

/****************************************************************************************************/
