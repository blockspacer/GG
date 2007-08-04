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
   
/* This class is based on earlier work with GG by Tony Casale.  Thanks, Tony.*/

/** \file DynamicGraphic.h
    Contains the DynamicGraphic class, a control that allows display of a slideshow or animated sequence of images. */

#ifndef _GG_DynamicGraphic_h_
#define _GG_DynamicGraphic_h_

#include <GG/Control.h>


namespace GG {
class Texture;

/** a control that replays images in sequence, forwards or backwards, animated or one frame at a time.  Frames of
    animation are stored in GG::Textures.  The frames are assumed to be laid out int rows from right to left, top to
    bottom, like text.  The location of each frame is calculated by DynamicGraphic; the user just needs to lay out the
    frames in the right order in the Texture(s) and give them to DynamicGraphic.  If a Texture is to be used that has
    "dead space" where there are no frames, that space must be at the end of the Texture, and the number of frames in
    the Texture should be supplied when the Texture is added.  When laying out the frames in the textures, the user can
    leave a margin between the frames and between the frames and the edge of the overall image, to make Texture creation
    and editing easier.  The width of this margin must be supplied to DynamicGraphic's ctor, and is constant once set.
    The margin applies to the top and left of \a each image, so the margins at the right and bottom edges of the texture
    are optional.  The multiple-Texture ctor assumes that all Textures but the last are packed with frames; if you need
    to specify multiple Textures with dead space, construct using the single-Texture ctor and use AddFrames().  Note
    that DynamicGraphic doesn't have "animated" in its name; it can replay images at any speed, and moreover it can be
    used as a sort of slideshow, and doesn't necessarily need to be animated at all. \note This is a situation in which
    the "last+1" idiom used throughout GG does not apply; when you set the end frame index to N, the last frame to be
    shown will be N, not N - 1. Also, while this control does not need to be the same size as the frames replayed within
    it, the size of the frames is taken from the size of the control when it is contructed. */
class GG_API DynamicGraphic : public Control
{
public:
    /** \name Signal Types */ //@{
    /** emitted whenever playback ends because the last frame was reached and Looping() == false; the argument is the
        index of the last frame (may be the first frame, if playing in reverse).  \note Unlike most other signals, this
        one is emitted during the execution of Render(), so keep this in mind when processing this signal.*/
    typedef boost::signal<void (int)> StoppedSignalType;

    /** emitted whenever the last frame of animation is reached; the argument is the index of the last frame (may be the
        first frame, if playing in reverse).  \note Unlike most other signals, this one is emitted during the execution
        of Render(), so keep this in mind when processing this signal.*/
    typedef boost::signal<void (int)> EndFrameSignalType;
    //@}

    /** \name Slot Types */ //@{
    typedef StoppedSignalType::slot_type StoppedSlotType;    ///< type of functor(s) invoked on a StoppedSignalType
    typedef EndFrameSignalType::slot_type EndFrameSlotType;  ///< type of functor(s) invoked on a EndFrameSignalType
    //@}

    /** \name Structors */ //@{
    /** ctor taking a vector of GG::Textures and the number of frames in those Textures.  The default \a frames value -1
        indicates all possible area is considered to contain valid frames.  Regardless of the value of \a frames, all
        Textures but the last are assumed to have the maximum number of frames based on their sizes.  This ctor allows
        specification of a frame size different from the size of the DynamicGraphic's size. */
    DynamicGraphic(int x, int y, int w, int h, bool loop, int frame_width, int frame_height, int margin, const std::vector<boost::shared_ptr<Texture> >& textures, Uint32 style = 0, int frames = -1, Uint32 flags = 0);
    //@}

    /** \name Accessors */ //@{
    int     Frames() const;      ///< returns the total number of frames in all the Textures that make up the animated sequence
    bool    Playing() const;     ///< returns true if the animation is running
    bool    Looping() const;     ///< returns true if playback is looping instead of stopping when it reaches the end
    double  FPS() const;         ///< returns the number of frames playing per second; may be positive, 0, or negative
    int     FrameIndex() const;  ///< returns the index of the currently-shown frame; -1 if none
    int     TimeIndex() const;   ///< returns the time in ms (measured from the time of the first frame); -1 if none

    /** returns the index of the earliest frame to be shown during playback.  \note when playing backwards this will be the last frame shown. */
    int     StartFrame() const;

    /** returns the index of the latest frame to be shown during playback.  \note when playing backwards this will be the first frame shown. */
    int     EndFrame() const;

    int     Margin() const;      ///< returns the number of pixels placed between frames and between the frames and the Texture edges
    int     FrameWidth() const;  ///< returns the original width of the control (and the width of the frame images)
    int     FrameHeight() const; ///< returns the original height of the control (and the height of the frame images)

    /** returns the style of the DynamicGraphic \see StaticGraphicStyle */
    Uint32  Style() const;

    mutable StoppedSignalType  StoppedSignal;  ///< the stopped signal object for this DynamicGraphic
    mutable EndFrameSignalType EndFrameSignal; ///< the end-frame signal object for this DynamicGraphic
    //@}

    /** \name Mutators */ //@{
    virtual void Render();

    /** adds a set of frames from Texture \a texture to the animation.  If \a frames == -1, the Texture is assumed to
        contain the maximum possible number of frames based on its size and the frame size.  \warning Calling code
        <b>must not</b> delete \a texture; \a texture becomes the property of a shared_ptr inside the DynamicGraphic.
        \throw GG::DynamicGraphic::CannotAddFrame Throws if \a texture is not large enough to contain any frames.*/
    void AddFrames(const Texture* texture, int frames = -1);

    /** adds a set of frames from Texture \a texture to the animation.  If \a frames == -1, the Texture is assumed to
        contain the maximum possible number of frames based on its size and the frame size.  \throw
        GG::DynamicGraphic::CannotAddFrame Throws if \a texture is not large enough to contain any frames.*/
    void AddFrames(const boost::shared_ptr<Texture>& texture, int frames = -1);

    /** adds a set of frames from Texture \a texture to the animation.  If \a frames == -1, the Textures are assumed to
        contain the maximum possible number of frames based on its size and the frame size.  Regardless of the value of
        \a frames, all Textures but the last are assumed to have the maximum number of frames based on their sizes.
        \throw GG::DynamicGraphic::CannotAddFrame Throws if no texture in \a textures is large enough to contain any
        frames.*/
    void AddFrames(const std::vector<boost::shared_ptr<Texture> >& textures, int frames = -1);

    void  Play();                    ///< starts the animation of the image
    void  Pause();                   ///< stops playback without adjusting the frame index
    void  NextFrame();               ///< increments the frame index by 1.  If Looping() == true and the next frame would be be past the last, the first frame is shown.  Pauses playback.
    void  PrevFrame();               ///< decrements the frame index by 1.  If Looping() == true and the next frame would be be past the first, the last frame is shown.  Pauses playback.
    void  Stop();                    ///< stops playback and resets the frame index to 0
    void  Loop(bool b = true);       ///< turns looping of playback on or off

    /** sets the frames per second playback speed (default is 15.0 FPS).  Negative rates indicate reverse playback.
        \note Calling SetFPS(0.0) is equivalent to calling Pause(). */
    void  SetFPS(double fps);

    void  SetFrameIndex(int idx);    ///< sets the frame index to \a idx ( value is locked to range [0, Frames()] )

    /** sets the frame index to the frame nearest time index \a idx, where \a idx measures time in ms from the beginning
        of the animation ( value is locked to range [0, Frames() * FPS()) ).  \note If looping is enabled, the time
        index may be any value >= 0.0, and values will "wrap" around the length of a loop.  If looping is disabled, any
        time index \a idx that is later than Frames() * FPS() is mapped to the last frame. */
    void  SetTimeIndex(int idx);

    /** sets the index of the first frame to be shown during playback ( value is locked to range [0, Frames()] ).  \note
        when playing backwards this will be the last frame shown. */
    void  SetStartFrame(int idx);

    /** sets the index of the last frame to be shown during playback ( value is locked to range [0, Frames()] ).  \note
        when playing backwards this will be the first frame shown. */
    void  SetEndFrame(int idx);

    /** sets the style flags, and perfroms sanity checking \see StaticGraphicStyle */
    void  SetStyle(Uint32 style);

    virtual void DefineAttributes(WndEditor* editor);
    //@}

    /** \name Exceptions */ //@{
    /** The base class for DynamicGraphic exceptions. */
    GG_ABSTRACT_EXCEPTION(Exception);

    /** Thrown when an attempt is made to add a frame to a DynamicGraphic which has no storage allocated for frames. */
    GG_CONCRETE_EXCEPTION(CannotAddFrame, GG::DynamicGraphic, Exception);
    //@}

protected:
    struct FrameSet
    {
        boost::shared_ptr<const Texture> texture; ///< the texture with the frames in it
        int                              frames;  ///< the number of frames in this texture

    private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive& ar, const unsigned int version);
    };

    /** \name Structors */ //@{
    DynamicGraphic(); ///< default ctor
    //@}

    /** \name Accessors */ //@{
    int FramesInTexture(const Texture* t) const; ///< returns the maximum number of frames that could be stored in \a t given the size of the control and Margin()

    const std::vector<FrameSet>& Textures() const;    ///< returns the shared_ptrs to texture objects with all animation frames

    int CurrentTexture() const;    ///< returns the current Texture being shown (part of it, anyway); -1 if none
    int CurrentSubTexture() const; ///< returns the current frame being shown within Texture number CurrTexture(); -1 if none
    int FirstFrameTime() const;    ///< returns the time index in ms that the first frame in the sequence was shown during the current playback; -1 if none
    int LastFrameTime() const;     ///< returns the time index in ms of the most recent frame shown (should be m_curr_frame); -1 if none
    //@}

    const int   m_margin;          ///< the number of pixels placed between frames and between the frames and the Texture edges
    const int   m_frame_width;     ///< the width of each frame 
    const int   m_frame_height;    ///< the height of each frame 

private:
    void ValidateStyle();            ///< ensures that the style flags are consistent

    std::vector<FrameSet> m_textures;///< shared_ptrs to texture objects with all animation frames

    double      m_FPS;               ///< current rate of playback in FPS
    bool        m_playing;           ///< set to true if playback is happening
    bool        m_looping;           ///< set to true if the playback should start over when it reaches the end
    int         m_curr_texture;      ///< the current Texture being shown (part of it, anyway); -1 if none
    int         m_curr_subtexture;   ///< the current frame being shown within Texture number \a m_curr_texture; -1 if none
    int         m_frames;            ///< the total number of frames in the animation
    int         m_curr_frame;        ///< the current absolute frame being shown; -1 if none
    int         m_first_frame_time;  ///< the time index in ms that the first frame in the sequence was shown during the current playback; -1 if none
    int         m_last_frame_time;   ///< the time index in ms of the most recent frame shown (should be m_curr_frame); -1 if none
    int         m_first_frame_idx;   ///< the index of the first frame shown during playback, usually 0
    int         m_last_frame_idx;    ///< the index of the last frame shown during playback. usually m_frames - 1

    Uint32      m_style;             ///< position of texture wrt the window area

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

} // namespace GG

// template implementations
template <class Archive>
void GG::DynamicGraphic::FrameSet::serialize(Archive& ar, const unsigned int version)
{
    boost::shared_ptr<Texture> non_const_texture;
    if (Archive::is_saving::value)
        non_const_texture = boost::const_pointer_cast<Texture>(texture);

    ar  & boost::serialization::make_nvp("texture", non_const_texture)
        & BOOST_SERIALIZATION_NVP(frames);

    if (Archive::is_loading::value)
        texture = boost::const_pointer_cast<const Texture>(non_const_texture);
}

template <class Archive>
void GG::DynamicGraphic::serialize(Archive& ar, const unsigned int version)
{
    ar  & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Control)
        & boost::serialization::make_nvp("m_margin", const_cast<int&>(m_margin))
        & boost::serialization::make_nvp("m_frame_width", const_cast<int&>(m_frame_width))
        & boost::serialization::make_nvp("m_frame_height", const_cast<int&>(m_frame_height))
        & BOOST_SERIALIZATION_NVP(m_textures)
        & BOOST_SERIALIZATION_NVP(m_FPS)
        & BOOST_SERIALIZATION_NVP(m_playing)
        & BOOST_SERIALIZATION_NVP(m_looping)
        & BOOST_SERIALIZATION_NVP(m_curr_texture)
        & BOOST_SERIALIZATION_NVP(m_curr_subtexture)
        & BOOST_SERIALIZATION_NVP(m_frames)
        & BOOST_SERIALIZATION_NVP(m_curr_frame)
        & BOOST_SERIALIZATION_NVP(m_first_frame_time)
        & BOOST_SERIALIZATION_NVP(m_last_frame_time)
        & BOOST_SERIALIZATION_NVP(m_first_frame_idx)
        & BOOST_SERIALIZATION_NVP(m_last_frame_idx)
        & BOOST_SERIALIZATION_NVP(m_style);

    if (Archive::is_loading::value)
        ValidateStyle();
}

#endif // _GG_DynamicGraphic_h_