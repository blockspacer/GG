/*
    Copyright 2005-2007 Adobe Systems Incorporated
    Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
    or a copy at http://stlab.adobe.com/licenses.html)
*/

/****************************************************************************************************/

// .hpp needs to come before widget_factory to hook the overrides
#include <GG/adobe/future/widgets/headers/platform_edit_text.hpp>

#include <GG/adobe/future/widgets/headers/edit_text_factory.hpp>
#include <GG/adobe/future/widgets/headers/widget_factory.hpp>
#include <GG/adobe/future/widgets/headers/widget_factory_registry.hpp>
#include <GG/adobe/layout_attributes.hpp>

/****************************************************************************************************/

namespace adobe {

/****************************************************************************************************/

void create_widget(const dictionary_t&   parameters,
                   size_enum_t           size,
                   edit_text_t*&         widget)
{
    edit_text_ctor_block_t block;

    get_value(parameters, key_name, block.name_m);
    get_value(parameters, key_alt_text, block.alt_text_m);
    get_value(parameters, key_characters, block.min_characters_m);
    get_value(parameters, key_max_characters, block.max_characters_m);
    get_value(parameters, key_lines, block.num_lines_m);
    get_value(parameters, static_name_t("read_only"), block.read_only_m);
    get_value(parameters, static_name_t("terminal_style"), block.terminal_style_m);
    get_value(parameters, static_name_t("wrap"), block.wrap_m);
    get_value(parameters, key_scrollable, block.scrollable_m);
    get_value(parameters, key_password, block.password_m);
    implementation::get_color(parameters, static_name_t("color"), block.color_m);
    implementation::get_color(parameters, static_name_t("text_color"), block.text_color_m);
    implementation::get_color(parameters, static_name_t("interior_color"), block.interior_color_m);

    widget = new edit_text_t(block);
}

/****************************************************************************************************/

namespace implementation {

/****************************************************************************************************/

widget_node_t make_edit_text(const dictionary_t&     parameters, 
                             const widget_node_t&    parent, 
                             const factory_token_t&  token,
                             const widget_factory_t& factory)
{ 
     return create_and_hookup_widget<edit_text_t, poly_placeable_t>(
        parameters,
        parent,
        token, 
        factory.is_container(static_name_t("edit_text")),
        factory.layout_attributes(static_name_t("edit_text"))); 
}

/****************************************************************************************************/

} // namespace implementation

/****************************************************************************************************/

} // namespace adobe

/****************************************************************************************************/
