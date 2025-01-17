//
//
//
#include <ArduinoJson.h>

#include "Config.h"

#include "SettingsHelper.h"
#include "OledFunctions.h"

const char *settingsFile = "settings.json";
const char *settingsBackupFile = "settingsbak.json";
const size_t settings_bufferSize = 10 * JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(9) + 9 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + 640;

void loadSettings()
{
    uint64_t fileSize = 0;
    if (fatfs.exists(settingsFile))
    {

        // Open file for reading
        auto file = fatfs.open(settingsFile);
        fileSize = file.size();
        StaticJsonDocument<settings_bufferSize> jsonDoc;

        if (deserializeJson(jsonDoc, file) == DeserializationError::Ok)
        {
#if DEBUG
            serializeJsonPretty(jsonDoc, Serial);
#endif

            JsonArray functypes = jsonDoc["functypes"];
            for (size_t i = 0; i < functypes.size(); i++)
            {
                settings.functypes[i] = functypes[i].as<String>();
            }

            JsonArray connectionconfigs = jsonDoc["connectionconfigs"];

            for (size_t i = 0; i < connectionconfigs.size(); i++)
            {
                const char *bt_addressess_name = connectionconfigs[i]["name"];
                const char *bt_addressess_address = connectionconfigs[i]["address"];
                strcpy(settings.connectionconfigs[i].address, bt_addressess_address);
                strcpy(settings.connectionconfigs[i].name, bt_addressess_name);
                settings.connectionconfigs[i].mouseaccel[0] = connectionconfigs[i][0];
                settings.connectionconfigs[i].mouseaccel[1] = connectionconfigs[i][1];
            }

            int bt_connect = jsonDoc["bluetoothAutoConnect"];
            settings.bluetoothAutoConnect = bt_connect;
            settings.lastconnected = jsonDoc["lastconnected"].as<String>();
            if (bt_connect != 0)
            {
                currentConnectionConfig = settings.connectionconfigs[bt_connect];
            }
            else
            {
                currentConnectionConfig = getConfigByName(settings.lastconnected);
            }
        }
        else
        {
            Serial.println(F("Failed to read file, using default configuration"));
#if DEBUG
            Serial.print(F("Contents of file "));
            Serial.println(settingsFile);
            while (file.available())
            {
                Serial.print((char)file.read());
            }
#endif // DEBUG
        }
        jsonDoc.clear();

        // Close the file (File's destructor doesn't close the file)
        file.close();
    }
    if (!fatfs.exists(settingsFile))
    {
        Serial.println(F("Uhm... There is no settings file"));
        saveSettings(); // Making a new settings file
    }
    else if (fileSize == 0)
    {
        Serial.println(F("The settings file is empty."));
        saveSettings();
    }
#if DEBUG
    Serial.println(F("Using the following settings"));
    Serial.print(F("functypes\t"));
    for (auto &functype : settings.functypes)
    {
        Serial.print(functype);
        Serial.print(F(" "));
    }
    Serial.println();
    Serial.print(F("bluetoothAutoConnect\t"));
    Serial.println(settings.bluetoothAutoConnect);
    Serial.println(F("connectionconfigs"));
    for (ConnectionConfig connectionconfig : settings.connectionconfigs)
    {
        Serial.print(F("\tname\t"));
        Serial.print(connectionconfig.name);
        Serial.print(F("\taddress\t"));
        Serial.print(connectionconfig.address);
        Serial.print(F("\tmouseaccel\t"));
        Serial.print(connectionconfig.mouseaccel[0]);
        Serial.print("\t");
        Serial.print(connectionconfig.mouseaccel[1]);
        Serial.println();
    }
    Serial.print(F("lastconnected\t"));
    Serial.print(settings.lastconnected);
    Serial.println();
#endif
}

// Saves the configuration to a file
void saveSettings()
{
    if (!yesnoScreen(true, "Do you want to save?"))
    {
        if (yesnoScreen(true, "Do you want to reload?"))
        {
            loadSettings();
            return;
        }
    }
    // Move existing file, otherwise the configuration is appended to the file
    if (!fatfs.remove(settingsBackupFile))
    {
        
    }
    fatfs.rename(settingsFile, settingsBackupFile);

    // Open file for writing
    auto file = fatfs.open(settingsFile, FILE_WRITE);
    if (!file.isOpen())
    {
        Serial.println(F("Failed to create file"));
        return;
    }

    StaticJsonDocument<settings_bufferSize> jsonDoc;

    JsonArray functypes = jsonDoc.createNestedArray("functypes");
    for (auto &functype : settings.functypes)
    {
        functypes.add(functype);
    }
    JsonArray connectionconfigs = jsonDoc.createNestedArray("connectionconfigs");

    for (auto &connectionconfig : settings.connectionconfigs)
    {
        JsonObject connectionconfig_obj = connectionconfigs.createNestedObject();
        connectionconfig_obj["name"] = connectionconfig.name;
        connectionconfig_obj["address"] = connectionconfig.address;
        JsonArray mouseaccel = connectionconfig_obj.createNestedArray("mouseaccel");
        mouseaccel.add(connectionconfig.mouseaccel[0]);
        mouseaccel.add(connectionconfig.mouseaccel[1]);
    }

    jsonDoc["bluetoothAutoConnect"] = settings.bluetoothAutoConnect;
    jsonDoc["lastconnected"] = "Desktop";

    serializeJsonPretty(jsonDoc, Serial);

    // Serialize JSON to file
    if (serializeJson(jsonDoc, file) == 0)
    {
        Serial.println(F("Failed to write to file"));
    }

    jsonDoc.clear();
    // Close the file (File's destructor doesn't close the file)
    file.close();
}

// TODO: Return pointer
ConnectionConfig getConfigByName(String name)
{
    for (auto &connectionConfig : settings.connectionconfigs)
    {
        if (connectionConfig.name == name.begin())
        {
            return connectionConfig;
        }
    }
    return ConnectionConfig{};
}

// TODO: Return pointer
ConnectionConfig getConfigByBTAddress(String btaddress)
{
    for (auto &connectionConfig : settings.connectionconfigs)
    {
        if (connectionConfig.address == btaddress.begin())
        {
            return connectionConfig;
        }
    }
    return ConnectionConfig{};
}

void saveConnectionConfig(ConnectionConfig conConf)
{
    for (int i = 0; i < 9; i++)
    {
        if (!strcmp(settings.connectionconfigs[i].address, conConf.address))
        {
            settings.connectionconfigs[i] = conConf;
            return;
        }
        else if (!strcmp(settings.connectionconfigs[i].name, ""))
        {
            settings.connectionconfigs[i] = conConf;
            return;
        }
    }
}

ConnectionConfig createConnectionConfig()
{
    ConnectionConfig newConfig;
    inputScreen(30, "Enter name", ALPHABET).toCharArray(newConfig.name, 30);
    newConfig.mouseaccel[0] = inputScreen(5, "Enter X mouseaccel", NUMBERS).toFloat();
    newConfig.mouseaccel[1] = inputScreen(5, "Enter Y mouseaccel", NUMBERS).toFloat();
    return newConfig;
}
