//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SplashScene.h                             //
//            █ █        █ █        bootstrap_splashscreen                    //
//             ████████████                                                   //
//           █              █       Copyright (c) 2017                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __GameMemory_include_Scene_SplashScene_h__
#define __GameMemory_include_Scene_SplashScene_h__

//MonsterFramework
#include "MonsterFramework.h"

namespace bootstrap_splashscreen {

class SplashScene :
    public cc::LayerColor
{
    // Inner Types //
public:
    struct Options {
        std::function<void ()> onFinishedCallback;
    };


    // Create / Init //
public:
    CREATE_FUNC_OPTIONS(SplashScene, Options);
    SCENE_FUNC_OPTIONS (SplashScene, Options);
    INIT_OPTIONS       (Options);


    // Lifecycle Methods //
public:
    virtual void onEnterTransitionDidFinish() override;


    // Private Methods //
public:
    //Setup
    void setup();

    //Animation
    void startAmazingAnimation();
    void startN2OMattAnimation();

    //Load
    cc::Sprite* loadAndSetupSprite(const std::string &name);

    // iVars //
private:
    cc::Sprite *m_pN2OMattSprite;
    cc::Sprite *m_pAmazingCowSprite;

    Options     m_options;
};

} //namespace bootstrap_splashscreen
#endif // __GameMemory_include_Scene_SplashScene_h__
