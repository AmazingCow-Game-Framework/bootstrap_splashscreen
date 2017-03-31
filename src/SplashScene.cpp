//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        SplashScene.cpp                           //
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

//Header
#include "../include/SplashScene.h"

//Usings
using namespace bootstrap_splashscreen;
USING_NS_STD_CC_CD_MF;


////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
//Sprite
constexpr auto kVar_SpriteN2OMatt    = "kSpriteN2OMatt";
constexpr auto kVar_SpriteAmazingCow = "kSpriteAmazingCow";

constexpr auto kSpritePath_AmazingCow = "bootstrap_splashscreen/spritesheet/Sprite_AmazingCowLogo.png";
constexpr auto kSpritePath_N2OMatt    = "bootstrap_splashscreen/spritesheet/Sprite_N2OMatt.png";

//Effect
constexpr auto kEffectId_AmazingIntro   = "amazing_intro.wav";
constexpr auto kEffectPath_AmazingIntro = "bootstrap_splashscreen/sounds/amazing_intro.wav";


////////////////////////////////////////////////////////////////////////////////
// Create / Init                                                              //
////////////////////////////////////////////////////////////////////////////////
bool SplashScene::init(const Options &options)
{
    MF_LOG("SplashScene::init");

    if(!cc::LayerColor::initWithColor(cc::Color4B::WHITE))
        return false;

    m_options = options;
    MF_ASSERT_EX(
        m_options.onFinishedCallback != nullptr,
        "SplashScene::init",
        "Invalid onFinishedCallback"
    );

    //Setup
    setup();

    return true;
}


////////////////////////////////////////////////////////////////////////////////
// Lifecycle Methods                                                          //
////////////////////////////////////////////////////////////////////////////////
void SplashScene::onEnterTransitionDidFinish()
{
    MF_LOG("SplashScene::onEnterTransitionDidFinish");

    cc::LayerColor::onEnterTransitionDidFinish();
    startAmazingAnimation();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
//Setup
void SplashScene::setup()
{
    //Sprites
    m_pAmazingCowSprite = loadAndSetupSprite(kSpritePath_AmazingCow);
    m_pN2OMattSprite    = loadAndSetupSprite(kSpritePath_N2OMatt   );

    //Sounds
    auto fullpath = cc::FileUtils::getInstance()->fullPathForFilename(
        kEffectPath_AmazingIntro
    );

    MF_ASSERT_EX(
        fullpath.size() != 0,
        "SplashScene::setup"
        "Cannot load intro effect: (%s)",
        fullpath.c_str()
    );

    mf::AudioManager::instance()->loadEffect(
        kEffectId_AmazingIntro,
        fullpath
    );
}

//Animation
void SplashScene::startAmazingAnimation()
{
    MF_LOG("SplashScene::startAmazingAnimation");

    //Delays
    auto pStartDelay  = cc::DelayTime::create(0.5f);
    auto pMiddleDelay = cc::DelayTime::create(0.7f);
    //Fades
    auto pFadeIn  = cc::FadeTo::create(0.3f, 255);
    auto pFadeOut = cc::FadeTo::create(0.3f,   0);
    //Callbacks
    auto pSoundCallback = cc::CallFunc::create([this](){
        mf::AudioManager::instance()->playEffect(kEffectId_AmazingIntro);
    });
    auto pEndCallback = cc::CallFunc::create(
        CC_CALLBACK_0(SplashScene::startN2OMattAnimation, this)
    );

    //Build the animation.
    auto pSequence = cc::Sequence::create({
        pStartDelay,
        pSoundCallback,
        pFadeIn,
        pMiddleDelay,
        pFadeOut,
        pEndCallback
    });

    m_pAmazingCowSprite->runAction(pSequence);
}

void SplashScene::startN2OMattAnimation()
{
    MF_LOG("SplashScene::startN2OMattAnimation");

    //Fades
    auto pFadeIn  = cc::FadeTo::create(0.3f, 255);
    auto pFadeOut = cc::FadeTo::create(0.3f, 0);
    //Delays
    auto pDelay = cc::DelayTime::create(1.0f);
    //Callbacks
    auto pCallback = cc::CallFunc::create([this](){
        m_options.onFinishedCallback();
    });
    //Build the animation
    auto pSequence = cc::Sequence::create({
        pFadeIn,
        pDelay,
        pFadeOut,
        pCallback
    });

    m_pN2OMattSprite->runAction(pSequence);
}


//Load
cc::Sprite* SplashScene::loadAndSetupSprite(const std::string &name)
{
    //Load
    MF_LOG_EX(
        "SplashScene::loadAndSetupSprite",
        "Sprite (%s)",
        name.c_str()
    );

    auto pSprite = cc::Sprite::create(name);

    MF_ASSERT_EX(
        pSprite != nullptr,
        "SplashScene::loadAndSetupSprite",
        "Cannot load sprite (%s)",
        name.c_str()
    );

    //Setup
    mf::GraphicsHelper::setRelativePosition(50, 55, pSprite, this);
    pSprite->setOpacity(0);
    pSprite->setScale  (cc::Director::getInstance()->getContentScaleFactor());

    //Add
    this->addChild(pSprite);

    return pSprite;
}
