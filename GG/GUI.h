// -*- C++ -*-
/* GG is a GUI for SDL and OpenGL.
   Copyright (C) 2003 T. Zachary Laine

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
   whatwasthataddress@hotmail.com */
   
/** \file GUI.h
    Contains GUI class, which encapsulates the state and behavior of the entire GG GUI. */

#ifndef _GG_GUI_h_ 
#define _GG_GUI_h_

#ifndef _GG_Base_h_
#include <GG/Base.h>
#endif

#ifndef _GG_Font_h_
#include <GG/Font.h>
#endif

namespace boost { namespace archive {
    class xml_oarchive;
    class xml_iarchive;
} }

namespace GG {

class Wnd;
class EventPumpBase;
class ModalEventPump;
class PluginInterface;
class StyleFactory;
class Texture;
struct GUIImplData;

/** An abstract base for an GUI framework class to drive the GG GUI.  
    This class has all the essential services that GG requires: 
    - GUI initialization and emergency exit
    - GG event handling
    - rendering of GUI windows
    - entry into and cleanup after a "2D" mode, in case the app also uses non-orthographic 3D projections
    - registration into, removal from, and movement within a z-ordering of windows, including handling of "always-on-top" windows
    - handling of modal windows
    - drag-and-drop support
    - inter-frame time updates and FPS calculations
    - limits on FPS speed
    - access to the dimensions of the application window or screen
    - mouse state information
    - keyboard accelerators
    - management of fonts and textures
    <p>
    The user is required to provide several functions.  The most vital functions the user is required to provide are:
    Enter2DMode(), Exit2DMode(), DeltaT(), PollAndRender() [virtual private], and Run() [virtual private].  Without
    these GUI is pretty useless.  In addition, HandleEvent() must be driven from PollAndRender().  The code driving
    HandleEvent() must interact with the hardware and operating system, and supply the appropriate EventType's, key
    presses, and mouse position info to HandleEvent().  It is the author's recommendation that the user use SDL to do
    this.  See http://www.libsdl.org for more info.
    <p>
    Keyboard accelerators may be defined, as mentioned above.  Each defined accelerator has its own signal which is
    emitted each time the accelerator is detected.  Client code should listen to the appropriate signal to act on an
    accelerator invocation.  Each slot that is signalled with a keyboard accelerator should return true if it processed
    the accelerator, or false otherwise.  This lets GUI know whether or not it should create a keystroke event and
    process it normally, sending it to the Wnd that currently has focus.  Note that since signals can be connected to
    multiple slots, if even one slot returns true, no kestroke event is created.  It is perfectly legal to return false
    even if an accelerator is processed, as long as you also then want the focus Wnd to receive a keystroke event.
    Also, note that all accelerators are processed before, and possbily instead of, any key events.  So setting a plain
    "h" as a keyboard accelerator can (if it is processed normally by a slot) prevent any Wnd anywhere in your
    application from receiving "h" keystrokes.  To avoid this:
    - Define accelerators with modifier keys like CTRL and ALT, or
    - Have slots that process these accelerators return false, or
    - Do not connect anything to such an accelerator, in which case it will return false.
    <p>
    A GUI-wide StyleFactory can be set; this controls the actual types of controls and dialogs that are created when a
    control or dialog creates one (e.g. when FileDlg encounters an error and creates a ThreeButtonDlg).  This is
    overridden by any StyleFactory that may be installed in an individual Wnd.
    <p>
    A note about "button-down-repeat".  When you click on the down-button on a scroll-bar, you probably expect the the
    button's action (scrolling down one increment) to repeat when you hold down the button, much like the way kestrokes
    are repeated when you hold down a keyboard key.  This is in fact what happens, and it is accomplished by having the
    scroll and its buttons respond to extra LButtonDown events generated by the GUI.  These extra messages, occur
    ButtonDownRepeatDelay() milliseconds after the button is first depressed, repeating every ButtonDownRepeatInterval()
    milliseconds thereafter.  Only Wnds created with the REPEAT_BUTTON_DOWN flag receive such extra messages.
*/
class GG_API GUI
{
private:
    struct OrCombiner 
    {
        typedef bool result_type; 
        template<class InIt> bool operator()(InIt first, InIt last) const;
    };

public:
    /** \name Signal Types */ //@{
    /** emitted when a keyboard accelerator is invoked. A return value of true indicates that the accelerator was processed 
        by some slot; otherwise, a keystroke event is processed instead. */
    typedef boost::signal<bool (), OrCombiner> AcceleratorSignalType;
    //@}

    /** \name Slot Types */ //@{
    typedef AcceleratorSignalType::slot_type   AcceleratorSlotType; ///< type of functor(s) invoked on a AcceleratorSignalType
    //@}

    /// these are the only events absolutely necessary for GG to function properly
    enum EventType {
        IDLE,        ///< nothing has changed since the last message, but the GUI might want to update some things anyway
        KEYPRESS,    ///< a down key press or key repeat, with or without modifiers like Alt, Ctrl, Meta, etc.
        KEYRELEASE,  ///< a key release, with or without modifiers like Alt, Ctrl, Meta, etc.
        LPRESS,      ///< a left mouse button press
        MPRESS,      ///< a middle mouse button press
        RPRESS,      ///< a right mouse button press
        LRELEASE,    ///< a left mouse button release
        MRELEASE,    ///< a middle mouse button release
        RRELEASE,    ///< a right mouse button release
        MOUSEMOVE,   ///< movement of the mouse; may include relative motion in addition to absolute position
        MOUSEWHEEL   ///< rolling of the mouse wheel; this event is accompanied by the amount of roll in the y-component of the mouse's relative position (+ is up, - is down)
    };

    typedef std::set<std::pair<Key, Uint32> >::const_iterator const_accel_iterator; ///< the type of iterator returned by accel_begin() and accel_end()

    typedef void (*SaveWndFn)(const Wnd* wnd, const std::string& name, boost::archive::xml_oarchive& ar);
    typedef void (*LoadWndFn)(Wnd*& wnd, const std::string& name, boost::archive::xml_iarchive& ar);

    /** \name Structors */ //@{
    virtual ~GUI(); ///< virtual dtor
    //@}

    /** \name Accessors */ //@{
    const std::string&
                   AppName() const;              ///< returns the user-defined name of the application
    Wnd*           FocusWnd() const;             ///< returns the GG::Wnd that currently has the input focus
    Wnd*           GetWindowUnder(const Pt& pt) const; ///< returns the GG::Wnd under the point pt
    int            DeltaT() const;               ///< returns ms since last frame was rendered
    virtual int    Ticks() const = 0;            ///< returns ms since the app started running
    bool           FPSEnabled() const;           ///< returns true iff FPS calulations are turned on
    double         FPS() const;                  ///< returns the frames per second at which the GUI is rendering
    std::string    FPSString() const;            ///< returns a string of the form "[m_FPS] frames per second"
    double         MaxFPS() const;               ///< returns the maximum allowed frames per second of rendering speed.  0 indicates no limit.
    virtual int    AppWidth() const = 0;         ///< returns the width of the application window/screen
    virtual int    AppHeight() const = 0;        ///< returns the height of the application window/screen
    int            ButtonDownRepeatDelay() const;///< returns the \a delay value set by EnableMouseButtonDownRepeat()
    int            ButtonDownRepeatInterval() const; ///< returns the \a interval value set by EnableMouseButtonDownRepeat()
    int            DoubleClickInterval() const;  ///< returns the maximum interval allowed between clicks that is still considered a double-click, in ms
    int            MinDragTime() const;          ///< returns the minimum time (in ms) an item must be dragged before it is a valid drag
    int            MinDragDistance() const;      ///< returns the minimum distance an item must be dragged before it is a valid drag
    bool           MouseButtonDown(int bn) const;///< returns the up/down states of the mouse buttons
    Pt             MousePosition() const;        ///< returns the absolute position of mouse, based on the last mouse motion event
    Pt             MouseMovement() const;        ///< returns the relative position of mouse, based on the last mouse motion event
    Uint32         KeyMods() const;              ///< returns the bitwise or'd set of modifier keys that are currently depressed, based on the last event

    const boost::shared_ptr<StyleFactory>& GetStyleFactory() const; ///< returns the currently-installed default style factory

    const_accel_iterator accel_begin() const;    ///< returns an iterator to the first defined keyboard accelerator
    const_accel_iterator accel_end() const;      ///< returns an iterator to the last + 1 defined keyboard accelerator

    /** returns the signal that is emitted when the requested keyboard accelerator is invoked. */
    AcceleratorSignalType& AcceleratorSignal(Key key, Uint32 key_mods) const;
    //@}

    /** \name Mutators */ //@{
    void           operator()();                 ///< external interface to Run()
    virtual void   Exit(int code) = 0;           ///< does basic clean-up, then calls exit(); callable from anywhere in user code via GetGUI()
    
    /** handles all waiting system events (from SDL, DirectInput, etc.).  This function should only be called from
        custom EventPump event handlers. */
    virtual void   HandleSystemEvents() = 0;

    void           SetFocusWnd(Wnd* wnd);        ///< sets the input focus window to \a wnd
    virtual void   Wait(int ms);                 ///< suspends the GUI thread for \a ms milliseconds.  Singlethreaded GUI subclasses may do nothing here, or may pause for \a ms milliseconds; the default implementation does nothing.
    void           Register(Wnd* wnd);           ///< adds \a wnd into the z-list.  Registering a null pointer or registering the same window multiple times is a no-op.
    void           RegisterModal(Wnd* wnd);      ///< adds \a wnd onto the modal windows "stack"
    void           Remove(Wnd* wnd);             ///< removes \a wnd from the z-list.  Removing a null pointer or removing the same window multiple times is a no-op.
    void           WndDying(Wnd* wnd);           ///< removes \a wnd from all GUI state variables, so that none of them point to a deleted object
    void           MoveUp(Wnd* wnd);             ///< moves \a wnd to the top of the z-list
    void           MoveDown(Wnd* wnd);           ///< moves \a wnd to the bottom of the z-list

    virtual boost::shared_ptr<ModalEventPump>
                   CreateModalEventPump(bool& done); ///< creates a new ModalEventPump that will terminate when \a done is set to true

    /** adds \a wnd to the set of current drag-and-drop Wnds, to be rendered \a offset pixels from the cursor
        position. \a originating_wnd indicates the original owner of \a wnd before the drag-drop.  \throw
        std::runtime_error May throw std::runtime_error if there are already other Wnds registered that belong to a
        window other than \a originating_wnd. */
    void           RegisterDragDropWnd(Wnd* wnd, const Pt& offset, Wnd* originating_wnd);

    void           CancelDragDrop();             ///< clears the set of current drag-and-drop Wnds
    virtual void   Enter2DMode() = 0;            ///< saves any current GL state, sets up GG-friendly 2D drawing mode.  GG expects an orthographic projection, with the origin in the upper left corner, and with one unit of GL space equal to one pixel on the screen.
    virtual void   Exit2DMode() = 0;             ///< restores GL to its condition prior to Enter2DMode() call
    void           EnableFPS(bool b = true);     ///< turns FPS calulations on or off
    void           SetMaxFPS(double max);        ///< sets the maximum allowed FPS, so the render loop does not act as a spinlock when it runs very quickly.  0 indicates no limit.
    void           EnableMouseButtonDownRepeat(int delay, int interval); ///< delay and interval are in ms; Setting delay to 0 disables mouse button-down repeating completely.
    void           SetDoubleClickInterval(int interval); ///< sets the maximum interval allowed between clicks that is still considered a double-click, in ms
    void           SetMinDragTime(int time);     ///< sets the minimum time (in ms) an item must be dragged before it is a valid drag
    void           SetMinDragDistance(int distance); ///< sets the minimum distance an item must be dragged before it is a valid drag

    /** establishes a keyboard accelerator.  Any key modifiers may be specified, or none at all. */
    void           SetAccelerator(Key key, Uint32 key_mods);

    /** removes a keyboard accelerator.  Any key modifiers may be specified, or none at all. */
    void           RemoveAccelerator(Key key, Uint32 key_mods);

    boost::shared_ptr<Font>    GetFont(const std::string& font_filename, int pts, Uint32 range = Font::ALL_CHARS); ///< returns a shared_ptr to the desired font
    void                       FreeFont(const std::string& font_filename, int pts); ///< removes the desired font from the managed pool; since shared_ptr's are used, the font may be deleted much later

    /** adds an already-constructed texture to the managed pool \warning calling code <b>must not</b> delete \a texture; the texture pool will do that. */
    boost::shared_ptr<Texture> StoreTexture(Texture* texture, const std::string& texture_name);

    boost::shared_ptr<Texture> StoreTexture(boost::shared_ptr<Texture> texture, const std::string& texture_name); ///< adds an already-constructed texture to the managed pool
    boost::shared_ptr<Texture> GetTexture(const std::string& name, bool mipmap = false); ///< loads the requested texture from file \a name; mipmap textures are generated if \a mipmap is true
    void                       FreeTexture(const std::string& name); ///< removes the desired texture from the managed pool; since shared_ptr's are used, the texture may be deleted much later

    void SetStyleFactory(const boost::shared_ptr<StyleFactory>& factory) const; ///< sets the currently-installed default style factory

    /** saves \a wnd to the archive \a ar, with the xml tag \a name.  \throw GG::GUI::BadFunctionPointer Throws
        GG::GUI::BadFunctionPointer if no Wnd-serializing function has ben defined by the user using
        SetSaveWndFunction(). */
    void SaveWnd(const Wnd* wnd, const std::string& name, boost::archive::xml_oarchive& ar);

    /** loads \a wnd, with the xml tag \a name, from the archive \a ar.  \throw GG::GUI::BadFunctionPointer Throws
        GG::GUI::BadFunctionPointer if no Wnd-serializing function has ben defined by the user using
        SetLoadWndFunction(). */
    void LoadWnd(Wnd*& wnd, const std::string& name, boost::archive::xml_iarchive& ar);

    /** Since LoadWnd() will only accept a referemce to a GG::Wnd*, this method is provided to more conveniently accept
        pointers to Wnd subclasses. */
    template <class T>
    void LoadWnd(T*& wnd, const std::string& name, boost::archive::xml_iarchive& ar);

    void SetSaveWndFunction(SaveWndFn fn); ///< sets \a fn to be the function invoked when SaveWnd() is called.
    void SetLoadWndFunction(LoadWndFn fn); ///< sets \a fn to be the function invoked when LoadWnd() is called.

    /** sets all the SaveWnd() and LoadWnd() function pointers to be the functions provided by \a interface. */
    void SetSaveLoadFunctions(const PluginInterface& interface);
    //@}

    static GUI*  GetGUI();                ///< allows any GG code access to GUI framework by calling GUI::GetGUI()
    static void  RenderWindow(Wnd* wnd);  ///< renders a window (if it is visible) and all its visible descendents recursively

    /** \name Exceptions */ //@{
    /** The base class for GUI exceptions. */
    GG_ABSTRACT_EXCEPTION(Exception);

    /** Thrown when an attempt is made to invoke either of the save- or load-window functions before they have been set. */
    GG_CONCRETE_EXCEPTION(BadFunctionPointer, GG::GUI, Exception);
    //@}

protected:
    /** \name Structors */ //@{
    GUI(const std::string& app_name); ///< protected ctor, called by derived classes
    //@}

    /** \name Mutators */ //@{
    void           HandleGGEvent(EventType event, Key key, Uint32 key_mods, const Pt& pos, const Pt& rel); ///< event handler for GG events
    void           ProcessBrowseInfo();    ///< determines the current browse info mode, if any
    virtual void   RenderBegin() = 0;      ///< clears the backbuffer, etc.
    virtual void   Render();               ///< renders the windows in the z-list
    virtual void   RenderEnd() = 0;        ///< swaps buffers, etc.

    // EventPumpBase interface
    void SetFPS(double FPS);               ///< sets the FPS value based on the most recent calculation
    void SetDeltaT(int delta_t);           ///< sets the time between the most recent frame and the one before it, in ms
    //@}

    virtual void   Run() = 0;                    // initializes GUI state, then executes main event handler/render loop (PollAndRender())

private:
    Wnd*           ModalWindow() const;          // returns the current modal window, if any

    // returns the window under \a pt, sending Mouse{Enter|Leave} or DragDrop{Enter|Leave} as appropriate
    Wnd*           CheckedGetWindowUnder(const Pt& pt, Uint32 key_mods);

    static GUI*                           s_gui;
    static boost::shared_ptr<GUIImplData> s_impl;

    friend class EventPumpBase; ///< allows EventPumpBase types to drive GUI
};


/** returns true if lwnd == rwnd or if lwnd contains rwnd */
GG_API bool MatchesOrContains(const Wnd* lwnd, const Wnd* rwnd);


// template implementations
template<class InIt> 
bool GUI::OrCombiner::operator()(InIt first, InIt last) const
{
    bool retval = false;
    while (first != last)
        retval |= static_cast<bool>(*first++);
    return retval;
}

template <class T>
void GUI::LoadWnd(T*& wnd, const std::string& name, boost::archive::xml_iarchive& ar)
{
    Wnd* wnd_as_base = wnd;
    LoadWnd(wnd_as_base, name, ar);
    wnd = dynamic_cast<T*>(wnd_as_base);
    assert(wnd || !wnd_as_base);
}

} // namespace GG

#endif // _GG_GUI_h_
