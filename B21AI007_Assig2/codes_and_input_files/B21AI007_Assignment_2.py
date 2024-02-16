#!/usr/bin/env python
# coding: utf-8

# In[310]:


import pandas as pd 
import math 
import itertools
import time
import matplotlib.pyplot as plt


# ## Complete Assignment

# In[286]:


data = pd.read_csv("data.csv")
courses = pd.read_csv("courses.csv")
data


# In[287]:


courses


# In[288]:



for i in courses.index : 
    if courses["No. of Students"][i] <= 20 : 
        courses.drop( i , inplace = True ) 

courses.reset_index( inplace=True , drop = True )
courses


# In[289]:


for j in range(1 , 6) : 
    g = "Grade-" + str(j) 
    for i in range(len(data)) : 
        if(data[g][i] == 'B' or data[g][i] == 'B-') : 
            data[g][i] = 'N/A' 
            data['Preference-' + str(j)][i] = 'N/A'


# In[290]:


seniority={
        'UG 1':1,
        'UG 2':2,
        'UG 3':3,
        'UG 4':4,
        'M.Tech 1':5,
        'M.Tech-M.Tech 1' : 5 ,
        'M.Tech-PhD 1':6,
        'PhD 1':7,
        'M.Tech 2':8,
        'M.Tech-PhD 2':9,
        'PhD 2':10,
        'M.Tech-PhD 3':11,
        'PhD 3':12,
        'M.Tech-PhD 4':13,
        'PhD 4':14,
        'M.Tech-PhD 5':15,
        'PhD 5':16,
    }


# In[291]:


for j in range(1 , 6) : 
    p = "Preference-" + str(j) 

    for i in range(len(data)) :  
        
        prog = data['Program'][i] 
        
        course = data[p][i]
        if(course == 'N/A') : 
            continue
        temp_df = courses[courses['Course Name'] == course]
        if len(temp_df) == 0 : 
            continue
        offered_for = list(temp_df['Offered for'])[0]
        
        offered_for = offered_for.split('|')
        for k in offered_for:
            
            if(seniority[prog] <= seniority[k])  : 
                data[p][i] = 'N/A' 
                data['Grade-' + str(j)][i] = 'N/A'
                break

data


# In[292]:


def get_detail( data , course ) : 
    detail = []
    for num in range(1 , 6):
        column = "Preference-" + str( num ) 
        temp_data = data[data[column] == course] 
#         temp_list = list(temp['Roll Number']) 
        
        for i in temp_data.index : 
            if(temp_data['Program'][i] == 'UG 3') :
                detail.append( [1 , 5 - num , temp_data['Roll Number'][i]])
            elif temp_data['Program'][i] == 'UG 4' :
                detail.append( [2 , 5 - num , temp_data['Roll Number'][i]])
            elif temp_data['Program'][i] == 'M.Tech 1' or temp_data['Program'][i] == 'PhD 1' or temp_data['Program'][i] == 'M.Tech-PhD 1':
                detail.append( [3 , 5 - num , temp_data['Roll Number'][i]])
            elif temp_data['Program'][i] == 'M.tech 2' :
                detail.append( [4 , 5 - num , temp_data['Roll Number'][i]])
            elif temp_data['Program'][i] != 'N/A':
                detail.append( [5 , 5 - num , temp_data['Roll Number'][i]])
    detail.sort() 
    detail.reverse()
    return detail 


# In[293]:


def extract_credit( L_T_P ) : 
    L_T_P = L_T_P.split('-')
    credit = int(L_T_P[0]) + int(L_T_P[1]) + int(L_T_P[2])/2
    return credit


# In[294]:


def find_subsets(  l , n ) :
    return list(itertools.combinations( l , n ))


# In[295]:


def number_of_tas( courses , course , ta_per_credit_student) : 
    temp = courses[courses['Course Name'] == course ]
    num_students = list(temp['No. of Students'])[0] 
    credit = extract_credit( list(temp['Credits'])[0])  
    
    tas = math.ceil((num_students * credit) / ta_per_credit_student )
#     if num_students <= 20 : 
#         tas = 0 
    return tas


# In[297]:


course_details = {} 
ta_per_credit_per_student = int(input())
course_list = list(courses['Course Name'])
for i in range(len(course_list)) : 
    course = course_list[i] 
    ta_list = get_detail(data , course) 
    num_tas = number_of_tas(courses , course , ta_per_credit_per_student )
#     if num_tas == 0  : 
#         course_details[course] = []
#         continue
    ta_list = find_subsets(ta_list , num_tas ) 
    course_details[course] = ta_list 


# In[298]:


def check_constraint( to_assign , course ) : 
    ug = 0 
    total = len(to_assign) 
    phd = 0 
    for i in to_assign: 
        if i[2][0] == 'B' : 
            ug += 1 
        elif i[2][0] == 'P' or i[2][0] == 'D' : 
            phd += 1 
    num_students = list(courses[courses['Course Name']== course ]['No. of Students'])[0] 
    
    if phd < math.ceil(num_students/100) : 
        return False 
    elif ug > 0.6 * total : 
        return False 
    return True 


# In[299]:


allocation = {}
def backtracking_search( course_list , i , assigned , course_details) : 
    global allocation
    n = len(course_list) 
    if i == n : 
        allocation = assigned 
        return True 
    can_assign = False
    course = course_list[i] 
    for j in range(len(course_details[course]) ) : 
        to_assign = course_details[course][j] 
        flag = 0 
        for k in to_assign : 
            if k[2] in assigned : 
                flag = 1 
                break
        if not check_constraint(to_assign , course ) and flag == 0 : 
            flag = 1 
        if flag == 1 : 
            continue
        for k in to_assign: 
            assigned[k[2]] = course 
            
        can_assign = can_assign or backtracking_search(course_list , i + 1 , assigned , course_details) 
        if can_assign == True  : 
            allocation = assigned
            return True 
        for k in to_assign: 
            del assigned[k[2]]
    
    return False


# In[300]:


course_list = list(courses['Course Name'])

start_time = time.time()  
backtracking_search( course_list , 0 , {} , course_details) 
end_time = time.time()


# In[301]:


print(allocation)


# In[302]:


print("Execution Time is " , end = "")
print(end_time - start_time)


# In[303]:


course_ta = {} 
for i in allocation: 
    if allocation[i] in course_ta: 
        course_ta[allocation[i]].append(i) 
    else: 
        course_ta[allocation[i]] = [i] 


# In[304]:


for i in course_ta: 
    print(i , " -> " , end = "") 
    for j in course_ta[i] : 
        print( j , " ,", end = " ")
    print()
    


# In[305]:


Allocated = pd.DataFrame() 


# In[ ]:





# In[306]:


l1 = [] 
l2 = [] 
l3 = []
for i in allocation: 
    l1.append(i) 
    l2.append(allocation[i]) 
    temp = data[data['Roll Number'] == i]
    pref = 0 
    if(list(temp["Preference-1"])[0] == allocation[i] ) : 
        pref = 1
    elif(list(temp["Preference-2"])[0] == allocation[i] ) : 
        pref = 2
    elif(list(temp["Preference-3"])[0] == allocation[i] ) : 
        pref = 3
    elif(list(temp["Preference-4"])[0] == allocation[i] ) : 
        pref = 4
    elif(list(temp["Preference-5"])[0] == allocation[i] ) : 
        pref = 5
    l3.append( pref )
Allocated["Roll No."] = l1 
Allocated["Course Assigned"] = l2  
Allocated["Preference"] = l3


# In[307]:


from collections import Counter 
print(Counter(Allocated["Preference"])) 

Allocated


# In[311]:


preference_counts = Allocated['Preference'].value_counts()

# Plotting the pie chart
plt.figure(figsize=(8, 6))
plt.pie(preference_counts, labels=preference_counts.index, autopct='%1.1f%%', startangle=140)
plt.title('Preference Distribution')
plt.show()


# In[313]:


allocated_ta_data = data[data['Roll Number'].isin(allocation)  ]
allocated_ta_data


# In[315]:


program_counts = allocated_ta_data['Program'].value_counts()

program_counts.plot(kind='pie', autopct='%1.1f%%', startangle=90)
plt.title('Distribution of Programs')
plt.ylabel('')  
plt.show()


# In[308]:


data = pd.read_csv("data.csv")


# In[272]:


not_allocated_ta = [] 
for i in range(len(data)): 
    if( data['Roll Number'][i] not in allocation) : 
        not_allocated_ta.append(data["Roll Number"][i])


# In[273]:



Unallocated = data[data['Roll Number'].isin(not_allocated_ta)]


# In[274]:


Unallocated = Unallocated.reset_index(drop=True)


# In[275]:


Unallocated


# In[ ]:





# In[276]:


Unallocated.to_csv("unallocated_ta.csv" , index = False)


# In[277]:


Allocated.to_csv("allocated_ta.csv" , index = "False") 


# ## Incomplete Assignment

# In[278]:


data = pd.read_csv("data.csv")[0:30] # taking total ta applicatoins less than available 
courses = pd.read_csv("courses.csv")
data


# In[279]:


for j in range(1 , 6) : 
    g = "Grade-" + str(j) 
    for i in range(len(data)) : 
        if(data[g][i] == 'B' or data[g][i] == 'B-') : 
            data[g][i] = 'N/A' 
            data['Preference-' + str(j)][i] = 'N/A'


# In[280]:


for j in range(1 , 6) : 
    p = "Preference-" + str(j) 

    for i in range(len(data)) :  
        
        prog = data['Program'][i] 
        
        course = data[p][i]
        if(course == 'N/A') : 
            continue
        temp_df = courses[courses['Course Name'] == course]
        
        offered_for = list(temp_df['Offered for'])[0]
        
        offered_for = offered_for.split('|')
        for k in offered_for:
            
            if(seniority[prog] <= seniority[k])  : 
                data[p][i] = 'N/A' 
                data['Grade-' + str(j)][i] = 'N/A'
                break

data


# In[281]:


course_details = {} 
ta_per_credit_per_student = int(input())
course_list = list(courses['Course Name'])
for i in range(len(course_list)) : 
    course = course_list[i] 
    ta_list = get_detail(data , course) 
    num_tas = number_of_tas(courses , course , ta_per_credit_per_student )
    
    ta_list = find_subsets(ta_list , num_tas ) 
    course_details[course] = ta_list 


# In[282]:


allocation = {}
def backtracking_search( course_list , i , assigned , course_details) : 
    global allocation
    n = len(course_list) 
#     print(assigned)
    if i == n : 
        allocation = assigned 
        return True 
    can_assign = False
    course = course_list[i] 
    for j in range(len(course_details[course]) ) : 
        to_assign = course_details[course][j] 
        flag = 0 
        for k in to_assign : 
            if k[2] in assigned : 
                flag = 1 
                break
        if not check_constraint(to_assign , course ) and flag == 0 : 
            flag = 1 
        if flag == 1 : 
            continue
        for k in to_assign: 
            assigned[k[2]] = course 
            
        can_assign = can_assign or backtracking_search(course_list , i + 1 , assigned , course_details) 
        if can_assign == True  : 
            allocation = assigned
            return True 
        for k in to_assign: 
            del assigned[k[2]]
    return False


# In[283]:


course_list = list(courses['Course Name'])

start_time = time.time()  
backtracking_search( course_list , 0 , {} , course_details) 
end_time = time.time()


# In[284]:


print(allocation)


# Not allocated any of the ta's since total number of ta's required was more than available.

# In[ ]:





# In[ ]:




