#!/usr/bin/env python
# coding: utf-8

# In[11]:


import random


# In[12]:


file = open('samples.dat', 'w')


# In[13]:


random.seed()
bounds = 10000000000000000000000000000000000000000000000000
max_samples = 1000

# In[14]:

operations = 13

for i in range(max_samples):    
    sample1 = random.randint(-bounds ,bounds) 
    sample2 = random.randint(-bounds, bounds)
    if(i  < max_samples/operations):
        sample3 = sample1 + sample2
        writeString = str(sample1) + " + " + str(sample2) + " " + str(sample3) + "\n"
    elif(i  < 2*max_samples/operations):
        sample3 = sample1 - sample2
        writeString = str(sample1) + " - " + str(sample2) + " " + str(sample3) + "\n"
    elif(i  < 3*max_samples/operations):
        sample3 = sample1 > sample2
        writeString = str(sample1) + " > " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i  < 4*max_samples/operations):
        sample3 = sample1 < sample2
        writeString = str(sample1) + " < " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i < 5*max_samples/operations):
        sample3 = sample1 != sample2
        writeString = str(sample1) + " != " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i < 6*max_samples/operations):
        sample3 = sample1 + sample2
        writeString = str(sample1) + " += " + str(sample2) + " " + str(sample3) + "\n"
    elif(i < 7*max_samples/operations):
        sample3 = sample1 - sample2
        writeString = str(sample1) + " -= " + str(sample2) + " " + str(sample3) + "\n"
    elif(i  < 8*max_samples/operations):
        sample3 = sample1 >= sample2
        writeString = str(sample1) + " >= " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i < 9*max_samples/operations):
        sample3 = sample1 <= sample2
        writeString = str(sample1) + " <= " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i < 10*max_samples/operations):
        if(random.randint(0,2)):
            sample1 = sample2
        sample3 = sample1 == sample2
        writeString = str(sample1) + " == " + str(sample2) + " " + str(int(sample3)) + "\n"
    elif(i < 11*max_samples/operations):
        writeString = " - " + str(sample1) + " " + str(-sample1) + "\n"
    elif(i < 12*max_samples/operations):
        writeString = " ++ " + str(sample1) + " " + str(sample1 + 1) + "\n"
    else:
        writeString = " -- " + str(sample1) + " " + str(sample1 - 1) + "\n"
    file.write(writeString)
file.flush()



