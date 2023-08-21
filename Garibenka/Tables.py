import pandas as pd
import os
import pathlib

currentTable = list()
loadedFiles = list()
loadedModules = list()

# 1 file = 1 file
class File():
    def __init__(self, inFileName):
        self.fileName = inFileName
        self.modulesList = list()

# 1 sheet == 1 module
class Module():
    def __init__(self, inFileName, inModuleName):
        self.fromFile = inFileName
        self.moduleName = inModuleName
        self.wordsList = list()
        self.kanjiList = list()

    def AddToWords(self, inWord):
        self.wordsList.append(inWord)

    def AddToKanji(self, inKanji):
        self.kanjiList.append(inKanji)

    def GetModuleName(self):
        return self.moduleName
    
    def GetFileName(self):
        return self.fromFile
    
    def GetWordList(self):
        return self.wordsList
    
    def GetKanjiList(self):
        return self.kanjiList
    
    def GetAllLists(self):
        all = list()
        all = all + self.wordsList + self.kanjiList
        return all
    
    def PrintWordList(self):
        for word in self.wordsList:
            word.PrintContents()
        
    def PrintKanjiList(self):
        for kanji in self.kanjiList:
            kanji.PrintContents()


# 1 word/kanji == 1 symbol
class Symbol():
    def __init__(self, inSymbol, inReading, inMeaning):
        self.symbol = inSymbol
        self.reading = inReading
        self.meaning = inMeaning
        self.learnt = False

    def SetLearnt(self):
        self.learnt = True

    def GetSymbol(self):
        return self.symbol
    
    def GetReading(self):
        return self.reading
    
    def GetMeaning(self):
        return self.meaning

    def PrintContents(self):
        print(self.symbol,self.reading,self.meaning)

# def LoadTables():
#     global loadedFiles

    
#     for fileName in os.listdir('./Tables/'):
#         if fileName.endswith('.xlsx') or fileName.endswith('.xls'):
#             file = File(fileName)
#             loadedFiles.append(file)
#             for sheet in pd.ExcelFile(fileName).sheet_names:
#                 module = Module(sheet)
#                 sheetVocabDf = pd.read_excel(fileName, index_col=None, na_values=['NA'], usecols="A,B,C")
#                 sheetVocabDf = sheetVocabDf.iloc[1:]
#                 sheetVocabDict = sheetVocabDf.to_dict()
#                 print(sheetVocabDf)


#     vocabDf = pd.read_excel('Tables\JP_3_Course.xlsx', index_col=None, na_values=['NA'], usecols="A,B,C")
#     vocabDf = vocabDf.iloc[1:]
#     #tableDf.fillna(method='ffill', axis=0)
#     print(vocabDf)

def LoadFiles():
    global loadedFiles
    for fileName in os.listdir(str(pathlib.Path(__file__).parent.resolve()) + '\\Tables'):
        if fileName.endswith('.xlsx') or fileName.endswith('.xls'):
            loadedFiles.append(fileName)
    #print(loadedFiles)

def FilesToModules():
    global loadedFiles
    global loadedModules

    pathToDir = str(pathlib.Path(__file__).parent.resolve()) + '\\Tables\\'

    for file in range(len(loadedFiles)):
        for sheet in pd.ExcelFile(str(pathToDir+loadedFiles[file])).sheet_names:
            module = Module(loadedFiles[file], sheet)
            loadedModules.append(module)
            #print(sheet)
            vocabDf = pd.read_excel(str(pathToDir+loadedFiles[file]), sheet_name=sheet, index_col=None, na_values=['NA'], usecols="A,B,C")
            vocabDf = vocabDf.iloc[1:]
            vocabDf.dropna(thresh=3,axis=0,inplace=True)
            vocabDf.columns=['Symbol','Reading','Meaning']
            #print(vocabDf)
            for index, row in vocabDf.iterrows():
                symbol=Symbol(row['Symbol'],row['Reading'],row['Meaning'])
                module.AddToWords(symbol)
            #print(module.PrintWordList())

            kanjiDf = pd.read_excel(str(pathToDir+loadedFiles[file]), sheet_name=sheet, index_col=None, na_values=['NA'], usecols="D,E,F")
            kanjiDf = kanjiDf.iloc[1:]
            kanjiDf.dropna(thresh=3,axis=0,inplace=True)
            kanjiDf.columns=['Symbol','Reading','Meaning']
            for index, row in kanjiDf.iterrows():
                symbol=Symbol(row['Symbol'],row['Reading'],row['Meaning'])
                module.AddToKanji(symbol)
            #print(module.PrintKanjiList())
    # for i in loadedModules:
    #     for j in i.GetKanjiList():
    #         j.PrintContents()


# do i need this? probably not
# def FillCurrentTable(selectFile, selectModule, selectMode):
#     global loadedFiles
#     global loadedModules
#     global currentTable

def OutputToFiles():
    global loadedFiles
    global loadedModules
    
    pathToDir = str(pathlib.Path(__file__).parent.resolve()) + '\\Tables\\' + 'PyOutput.txt'

    with open(pathToDir, mode='w', encoding='utf-8') as textFile:
        for module in loadedModules:
            textFile.write(f'@{module.GetModuleName()}\n')
            textFile.write(f'#{module.GetFileName()}\n')
            for word in module.GetWordList():
                textFile.write(f'!{word.GetSymbol()}\t{word.GetReading()}\t{word.GetMeaning()}\n')
            for kanji in module.GetKanjiList():
                textFile.write(f'?{kanji.GetSymbol()}\t{kanji.GetReading()}\t{kanji.GetMeaning()}\n')

#Load everything
pathToDir = str(pathlib.Path(__file__).parent.resolve()) + '\\Tables\\' + 'PyOutput.txt'
open(pathToDir, 'w').close()
loadedFiles.clear()
loadedModules.clear()

LoadFiles()
FilesToModules()
OutputToFiles()
print("it's working")