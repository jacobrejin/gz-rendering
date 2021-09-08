/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_RENDERING_OGRE2_OGRE2SELECTIONBUFFER_HH_
#define IGNITION_RENDERING_OGRE2_OGRE2SELECTIONBUFFER_HH_

#include <memory>
#include <string>

#include "ignition/rendering/config.hh"
#include "ignition/rendering/ogre2/Export.hh"

namespace Ogre
{
  class Item;
  class RenderTarget;
  class SceneManager;
}

namespace ignition
{
  namespace rendering
  {
    inline namespace IGNITION_RENDERING_VERSION_NAMESPACE {
    //
    // forward declaration
    struct Ogre2SelectionBufferPrivate;

    /// \brief Generates a selection buffer object for a given camera.
    /// The selection buffer is used of entity selection. On setup, a unique
    /// color is assigned to each entity. Whenever a selection request is made,
    /// the selection buffer camera renders to a 1x1 sized offscreen buffer.
    /// The color value of that pixel gives the identity of the entity.
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2SelectionBuffer
    {
      /// \brief Constructor
      /// \param[in] _camera Name of the camera to generate a selection
      /// buffer for.
      /// \param[in] _scene Pointer to the scene
      /// \param[in] _width width of the camera
      /// \param[in] _height height of the camera
      public: Ogre2SelectionBuffer(const std::string &_cameraName,
                  Ogre2ScenePtr _scene, unsigned int _width,
                  unsigned int _height);

      /// \brief Destructor
      public: ~Ogre2SelectionBuffer();

      /// \brief Handle on mouse click
      /// \param[in] _x X coordinate in pixels.
      /// \param[in] _y Y coordinate in pixels.
      /// \return Returns the Ogre item at the coordinate.
      public: Ogre::Item *OnSelectionClick(const int _x, const int _y);

      /// \brief Set dimension of the selection buffer
      /// \param[in] _x X coordinate in pixels.
      /// \param[in] _y Y coordinate in pixels.
      public: void SetDimensions(unsigned int _width, unsigned int _height);

      /// \brief Debug show overlay
      /// \param[in] _show True to show the selection buffer in an overlay.
      // public: void ShowOverlay(const bool _show);

      /// \brief Call this to update the selection buffer contents
      public: void Update();

      /// \brief Delete the render texture
      private: void DeleteRTTBuffer();

      /// \brief Create the render texture
      private: void CreateRTTBuffer();

      /// \brief Create the selection buffer offscreen render texture.
      // private: void CreateRTTOverlays();

      /// \internal
      /// \brief Pointer to private data.
      private: std::unique_ptr<Ogre2SelectionBufferPrivate> dataPtr;
    };
    }
  }
}
#endif
