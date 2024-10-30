/*
 * GFW
 * Copyright (C) 2024   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef GFW_SETTINGS
#define GFW_SETTINGS

#include <string>

namespace GFW {

    class Settings {
        public:
            //!Gibt einen Zeiger auf die Instance der Klasse
            static Settings *Instance();

            /**
             * @brief Lade Einstellungen aus Datei
             */
            bool Load(std::string file);

            /**
             * @brief Gibt die Musiklautstärke zurück 0.0 = Mute 1.0 = Max
             */
            [[nodiscard]] float MusicVolume() const;

            /**
             * @brief Gibt die Effekt Lautstärke zurück 0.0 = Mute 1.0 = Max
             */
            [[nodiscard]] float EffectVolume() const;

            /**
             * @brief Gibt an, ob in Vollbild gestartet werden soll
             */
            [[nodiscard]] bool FullScreen() const;

            /**
             * @brief Werden Debuginformationen benötigt?
             *        Vielleicht gbt es auch noch eine Debug-Konsole oder so
             */
            [[nodiscard]] bool Debug() const;

            /**
             * @brief Gibt die Fensterbreite an
             */
            [[nodiscard]] int WindowWidth() const;

            /**
             * @brief Gibt die Fensterhöhe an
             */
            [[nodiscard]] int WindowHeight() const;

            /**
             * Gibt an, auf wie viel FPS im Vollbild gesetzt werden soll
             */
            [[nodiscard]] int FPS() const;

            /**
             * @brief Mit welcher Taste wird das  Programm beendet, ohne nachfrage.
             *        Funktion kommt von glfw, eventuell kann man es ausstellen?
             */
            [[nodiscard]] int ExitKey() const;

            /**
             * @brief Wie viel Text wird in der Konsole ausgegeben.
             */
            [[nodiscard]] int LogLevel() const;

            /**
             * @brief Wird die Programmversion mit angezeigt.
             *        Kann von jeder Anwendung individuell ignoriert werden
             */
            [[nodiscard]] bool ShowVersion() const;

            /**
             * @brief Setzen der Musiklautstärke, von 0.0 bis 1.0
             */
            void MusicVolume(float vol);

            /**
             * @brief Setzt die Effektlautstärke
             */
            void EffectVolume(float vol);

            /**
             * @biref Vollbild ein/aus schalten
             */
            void FullScreen(bool val);

            /**
             * @brief Stellt Debuginfos ein/aus
             */
            void Debug(bool val);

            /**
             * @brief Setzt die Fensterbreite.
             *        TODO: durch Bildschirmmodi ersetzten?
             */
            void WindowWidth(int width);

            /**
             * @brief Setzt die Fensterhöhe.
             *        TODO: durch Bildschirmmodi ersetzten?
             */
            void WindowHeight(int height);

            /**
             * @brief Setzt die FPS
             */
            void FPS(int fps);

            /**
             * @brief Setzt die Taste, mit der die Anwendung beendet wird
             */
            void ExitKey(int key);

            /**
             * @brief Setzt das loglevel
             */
            void LogLevel(int logLevel);

            /**
             * @brief Zeige/Verberge Version
             */
            void ShowVersion(bool version);

            /**
             * @brief Speichert die aktuellen Einstellungen in die Settingsdatei
             */
            void Save(std::string file) const;

            Settings(const Settings &) = delete;

            Settings(Settings &&) = delete;

            Settings &operator=(const Settings &) = delete;

            Settings &operator=(Settings &&) = delete;

        private:
            Settings();

            static Settings *privateInstance;

            float privateMusicVolume;    /*!< Musiklautstärke */
            float privateEffectVolume;   /*!< Effektlautstärke */
            bool privateFullscreen;      /*!< Vollbild Variable */
            bool privateCollisionBoxes;  /*!< Kollisionsboxen Variable */
            bool privateShowVersion;
            int privateWindowWidth;    /*!< Fensterbreite */
            int privateWindowHeight;   /*!< Fensterhöhe */
            int privateFPS;              /*!< Bilder pro Sekunde */
            int privateExitKey;
            int privateLogLevel;
        };

} // namespace GFW

#endif //GFW_SETTINGS
