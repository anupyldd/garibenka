import pandas as pd
import collections

userName = 'Username'
userSettings = dict()
currentLang = dict() #stores the language according to current user settings

def StartConfig():
    global userName

    settingsDf = pd.read_csv('Settings\settings.tsv', sep='\t', header=0)

    for i in range(len(settingsDf)):
        userSettings[settingsDf.loc[i, 'SettingName']] = settingsDf.loc[i, 'SettingValue']

    userName = userSettings['UserName']
    FillCurrentLang()

def SetUserName(inUserName):
    global userName

    #change in settings file
    with open('Settings\settings.tsv', 'r') as settingsFile:
        settingsData = settingsFile.read()
    settingsData = settingsData.replace(userName, inUserName)
    with open('Settings\settings.tsv', 'w') as settingsFile:
        settingsFile.write(settingsData)
    
    userName = userSettings['UserName']

def SetLanguage(shortLanName):
    global userSettings

    with open('Settings\settings.tsv', 'r') as settingsFile:
        settingsData = settingsFile.read()
    settingsData = settingsData.replace(userSettings['Language'], shortLanName)
    with open('Settings\settings.tsv', 'w') as settingsFile:
        settingsFile.write(settingsData)

    userSettings['Language'] = shortLanName

    StartConfig()
    #FillCurrentLang()

def ToggleTheme():
    global userSettings

    with open('Settings\settings.tsv', 'r') as settingsFile:
        settingsData = settingsFile.read()

        if userSettings['Theme'] == 'dark':
            settingsData = settingsData.replace(userSettings['Theme'], 'light')
            userSettings['Theme'] = 'light'
        else:
            settingsData = settingsData.replace(userSettings['Theme'], 'dark')
            userSettings['Theme'] = 'dark'

    with open('Settings\settings.tsv', 'w') as settingsFile:
        settingsFile.write(settingsData)
    
def FillCurrentLang():
    global currentLang
    global userSettings
    activeLang = userSettings['Language']

    locDf = pd.read_csv('Settings/loc.tsv', sep='\t', header=0)
    refCol = locDf['ref'].tolist()
    activeLangCol = locDf[activeLang].tolist()

    for i in range(len(refCol)):
        currentLang[refCol[i]] = activeLangCol[i]
    