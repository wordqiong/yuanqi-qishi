
#ifndef _SIMPLE_AUDIO_ENGINE_H_
#define _SIMPLE_AUDIO_ENGINE_H_

#include <stddef.h>
#include "Export.h"
#include <typeinfo>
#include <ctype.h>
#include <string.h>

namespace CocosDenshion {

    class TypeInfo
    {
    public:
        virtual long getClassTypeInfo() = 0;
    };

    static inline unsigned int getHashCodeByString(const char* key)
    {
        unsigned int len = strlen(key);
        const char* end = key + len;
        unsigned int hash;

        for (hash = 0; key < end; key++)
        {
            hash *= 16777619;
            hash ^= (unsigned int)(unsigned char)toupper(*key);
        }
        return (hash);
    }

    /**
    @class          SimpleAudioEngine
    @brief          offer a VERY simple interface to play background music & sound effect
    */

    class EXPORT_DLL SimpleAudioEngine : public TypeInfo
    {
    public:
        SimpleAudioEngine();
        ~SimpleAudioEngine();

        virtual long getClassTypeInfo() {
            return getHashCodeByString(typeid(CocosDenshion::SimpleAudioEngine).name());
        }

        /**
        @brief Get the shared Engine object,it will new one when first time be called
        */
        static SimpleAudioEngine* sharedEngine();

        /**
        @brief Release the shared Engine object
        @warning It must be called before the application exit, or a memroy leak will be casued.
        */
        static void end();

        /**
         @brief Preload background music
         @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
         */
        void preloadBackgroundMusic(const char* pszFilePath);

        /**
        @brief Play background music
        @param pszFilePath The path of the background music file,or the FileName of T_SoundResInfo
        @param bLoop Whether the background music loop or not
        */
        void playBackgroundMusic(const char* pszFilePath, bool bLoop);
        void playBackgroundMusic(const char* pszFilePath) {
            this->playBackgroundMusic(pszFilePath, false);
        }

        /**
        @brief Stop playing background music
        @param bReleaseData If release the background music data or not.As default value is false
        */
        void stopBackgroundMusic(bool bReleaseData);
        void stopBackgroundMusic() {
            this->stopBackgroundMusic(false);
        }

        /**
        @brief Pause playing background music
        */
        void pauseBackgroundMusic();

        /**
        @brief Resume playing background music
        */
        void resumeBackgroundMusic();

        /**
        @brief Rewind playing background music
        */
        void rewindBackgroundMusic();

        bool willPlayBackgroundMusic();

        /**
        @brief Whether the background music is playing
        @return If is playing return true,or return false
        */
        bool isBackgroundMusicPlaying();

        // properties
        /**
        @brief The volume of the background music max value is 1.0,the min value is 0.0
        */
        float getBackgroundMusicVolume();

        /**
        @brief set the volume of background music
        @param volume must be in 0.0~1.0
        */
        void setBackgroundMusicVolume(float volume);

        /**
        @brief The volume of the effects max value is 1.0,the min value is 0.0
        */
        float getEffectsVolume();

        /**
        @brief set the volume of sound effecs
        @param volume must be in 0.0~1.0
        */
        void setEffectsVolume(float volume);

        // for sound effects
        /**
        @brief Play sound effect
        @param pszFilePath The path of the effect file,or the FileName of T_SoundResInfo
        @bLoop Whether to loop the effect playing, default value is false
        */
        unsigned int playEffect(const char* pszFilePath, bool bLoop);
        unsigned int playEffect(const char* pszFilePath) {
            return this->playEffect(pszFilePath, false);
        }

        /**
        @brief Pause playing sound effect
        @param nSoundId The return value of function playEffect
        */
        void pauseEffect(unsigned int nSoundId);

        /**
        @brief Pause all playing sound effect
        @param nSoundId The return value of function playEffect
        */
        void pauseAllEffects();

        /**
        @brief Resume playing sound effect
        @param nSoundId The return value of function playEffect
        */
        void resumeEffect(unsigned int nSoundId);

        /**
        @brief Resume all playing sound effect
        @param nSoundId The return value of function playEffect
        */
        void resumeAllEffects();

        /**
        @brief Stop playing sound effect
        @param nSoundId The return value of function playEffect
        */
        void stopEffect(unsigned int nSoundId);

        /**
        @brief Stop all playing sound effects
        */
        void stopAllEffects();

        /**
        @brief          preload a compressed audio file
        @details        the compressed audio will be decode to wave, then write into an
        internal buffer in SimpleaudioEngine
        */
        void preloadEffect(const char* pszFilePath);

        /**
        @brief          unload the preloaded effect from internal buffer
        @param[in]        pszFilePath        The path of the effect file,or the FileName of T_SoundResInfo
        */
        void unloadEffect(const char* pszFilePath);
    };

} // end of namespace CocosDenshion

#endif // _SIMPLE_AUDIO_ENGINE_H_



