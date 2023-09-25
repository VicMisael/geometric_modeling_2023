import os
import glob

arquivos = r'*.o'

for file in glob.glob(arquivos, recursive=True):
    os.remove(file)