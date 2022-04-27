# -*- coding: utf-8 -*-
"""
Created on Mon Apr 25 13:29:57 2022

@author: fiacr
"""
import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np   
import seaborn as sns
os.chdir("C:/Users/fiacr/Desktop/EXOC/F_test_evo/")
print(os.getcwd())
data = pd.read_csv("C:/Users/fiacr/Desktop/EXOC/F_test_evo/doc3.csv",sep=';', names=["TAILLE","COLLISION"], header=0)
print(data.shape)
print(data["TAILLE"])
print(data["COLLISION"])
#x=data["TAILLE"]
#y=data["COLLISION"]
#plt.plot(x,y,lw=6)
#plt.xlabel("TAILLE")
#plt.ylabel("COLLISION")
plt.legend(["TAILLE","COLLISION"])
sns.pairplot(data)
