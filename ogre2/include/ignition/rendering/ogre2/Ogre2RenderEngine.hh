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
#ifndef IGNITION_RENDERING_OGRE2_OGRE2RENDERENGINE_HH_
#define IGNITION_RENDERING_OGRE2_OGRE2RENDERENGINE_HH_

#include <memory>
#include <string>
#include <vector>

#include <ignition/common/SingletonT.hh>

#include "ignition/rendering/RenderEnginePlugin.hh"
#include "ignition/rendering/base/BaseRenderEngine.hh"
#include "ignition/rendering/base/BaseRenderTypes.hh"
#include "ignition/rendering/ogre2/Ogre2RenderTypes.hh"
#include "ignition/rendering/ogre2/Export.hh"

namespace Ogre
{
  class LogManager;
  class Root;
  namespace v1
  {
    class OverlaySystem;
  }
}

namespace ignition
{
  namespace rendering
  {
    // forward declaration
    class Ogre2RenderEnginePrivate;

    /// \brief Plugin for loading ogre render engine
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2RenderEnginePlugin :
      public RenderEnginePlugin
    {
      /// \brief Constructor
      public: Ogre2RenderEnginePlugin();

      /// \brief Destructor
      public: ~Ogre2RenderEnginePlugin() = default;

      /// \brief Get the name of the render engine loaded by this plugin.
      /// \return Name of render engine
      public: std::string Name() const;

      /// \brief Get a pointer to the render engine loaded by this plugin.
      /// \return Render engine instance
      public: RenderEngine *Engine() const;
    };

    /// \brief Ogre2 render engine class. A singleton class that manages the
    /// underlying ogre2 render engine, loads its plugins, and creates
    /// resources needed for the engine to run
    class IGNITION_RENDERING_OGRE2_VISIBLE Ogre2RenderEngine :
      public virtual BaseRenderEngine,
      public common::SingletonT<Ogre2RenderEngine>
    {
      /// \brief Constructor
      private: Ogre2RenderEngine();

      /// \brief Destructor
      public: virtual ~Ogre2RenderEngine();

      // Documentation Inherited.
      public: virtual bool Fini();

      // Documentation Inherited.
      public: virtual bool IsEnabled() const;

      // Documentation Inherited.
      public: virtual std::string Name() const;

      /// \brief Add path to resourcea in ogre2's resource manager
      /// \param[in] _uri Reousrce path in the form of an uri
      public: void AddResourcePath(const std::string &_uri);

      /// \brief Get the ogre2 root object
      /// \return ogre2 root object
      public: virtual Ogre::Root *OgreRoot() const;

      /// \brief Create a render window
      /// \param[in] _handle Handle of native window which the render window
      ///  will attach
      /// \param[in] _width Width of render window
      /// \param[in] _height Height of render window
      /// \param[in] _ratio Device pixel ratio (typically needed for retina
      /// displays)
      /// \param[in] _antiAliasing Anti-aliasing level
      public: std::string CreateWindow(const std::string &_handle,
                  const unsigned int _width, const unsigned int _height,
                  const double _ratio, const unsigned int _antiAliasing);

      /// \brief Create a scene
      /// \param[in] _id Unique scene Id
      /// \parampin] _name Name of scene
      protected: virtual ScenePtr CreateSceneImpl(unsigned int _id,
                  const std::string &_name);

      /// \brief Get a pointer to the list of scenes managed by the render
      /// engine
      /// \return list of scenes
      protected: virtual SceneStorePtr Scenes() const;

      /// \brief Load the render engine
      /// \return True if the operation is successful
      protected: virtual bool LoadImpl();

      /// \brief Initialize the render engine
      /// \return True if the operation is successful
      protected: virtual bool InitImpl();

      /// \brief Helper function to initialize the render engine
      private: void LoadAttempt();

      /// \brief Create the ogre logger for logging ogre messages to file
      private: void CreateLogger();

      /// \brief Create GL context
      private: void CreateContext();

      /// \brief Create ogre root
      private: void CreateRoot();

      /// \brief Create ogre overlay component
      private: void CreateOverlay();

      /// \brief Create ogre plugins.
      private: void LoadPlugins();

      /// \brief Creat the ogre render system
      private: void CreateRenderSystem();

      /// \brief Create dummy 1x1 render window for the main rendering context
      private: void CreateWindow();

      /// \brief Create the resources needed by ogre
      private: void CreateResources();

      /// \brief Attempt to initialize engine and catch exeption if they occur
      private: void InitAttempt();

      /// \internal
      /// \brief Get a pointer to the Ogre overlay system.
      /// \return Pointer to the ogre overlay system.
      public: Ogre::v1::OverlaySystem *OverlaySystem() const;

      /// \brief Pointer to the ogre's overlay system
      private: Ogre::v1::OverlaySystem *ogreOverlaySystem = nullptr;

      /// \brief Flag to indicate if engine is loaded
      private: bool loaded = false;

      /// \brief Flag to indicate if engine is initialized
      private: bool initialized = false;

      /// \brief List of scenes managed by the render engine
      private: Ogre2SceneStorePtr scenes;

      /// \brief Ogre root
      private: Ogre::Root *ogreRoot = nullptr;

      /// \brief Ogre log manager
      private: Ogre::LogManager *ogreLogManager = nullptr;

      /// \brief Paths to ogre plugins
      private: std::vector<std::string> ogrePaths;

      /// \brief Dummy display needed for linux platform
      private: void *dummyDisplay = nullptr;

      /// \brief Dummy context needed for linux platform
      private: void *dummyContext = nullptr;

      /// \brief Dummy window Id needed for linux platform
      private: uint64_t dummyWindowId = 0u;

      /// \brief Pointer to private data
      private: std::unique_ptr<Ogre2RenderEnginePrivate> dataPtr;

      /// \brief Singleton setup
      private: friend class common::SingletonT<Ogre2RenderEngine>;
    };
  }
}
#endif

