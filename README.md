###ActivityNet: Mining Deep Knowledge from Big Social Data
===========================
####　　　　　　　　　　　　　　　　　　　------Predict social behaviors
####　　　　　　　　　　　　　　　　　　　　　　　[http://activitynet.info](http://activitynet.info)
===========================
####Introduction
ActivityNet is an activity mining and analytic framework, aiming to mining **deep knowledge** from big social data. We are currently working on the largest Chinese micro-blogging—Weibo, and have extracted *2,105,303* activities (users, location, activity, time) from *1 billion* tweets. We have built a knowledge network based on the extracted activities, which allows us to predict what, where and when your friends are doing. The system is also able to predict the probability that one activity happens after another activity. In addition, ActivityNet has following features: 

* **Activity search:** find the activity you want to know about;
* **Geography analysis:** disclose the popularity distribution of a particular activity over the world;
* **Sentiment analysis:** disclose how people think about the activity, like or not;
* **Time analysis:** disclose when a user will participate into an activity.

####System Applications
Several interesting applications are implemented under the ActivityNet framework:

* **Relevance Analysis:** Find top K most relevant activities for a given query. For example, for “gambling”, we find “play game”, “play poker”, “play golf”, etc.. This has been done by a deep learning-based method.
* **Location Analysis:** Where are people doing the activity? ActivityNet tells you, for example, that hotel is a hot place for “gambling”.
* **Geography Analysis:** We demonstrate the popularity distribution for a queried activity. From the result we see that Macau is a big city for “gambling”. User can also select the sentiment results to see how people from different cities like (or dislike) the queried activity.
* **Time Analysis: Time distribution of the queried activity.
* **Sentiment Analysis:** A sentiment analytic algorithm is employed to predict how many users like (or dislike) the activity.
* **Relevant Users:** Identify Weibo Users most relevant to the quieried activity.
* **Next Activity:** Predict the activity a user most likely to do after an activity.

####System Illustration
System applications can be illustrated in this combined Screenshot from real online website:

　　　　　　　　![](https://github.com/actnet/actnetdemo/blob/master/materials/demo.jpg)


####Acknowlegement
The system was developed by Tsinghua University Knowledge Engineering Group (KEG), sponsored by Huawei Technologies Co., Ltd.

####API
ActivitySearchByName (const string& input, string& output):  
Input: activity name  
Output: the most similar activity in saedb  

ActivitySearchSimilar(const string& input, string& output):  
Input: activity name, result size  
Output: the most similar n(n is result size) activities in saedb

ListSearchByActivity(const string& input, string& output):  
Input: activity name  
Output: all activities’s name in activity cluster

CenterSearchByActivity(const string& input, string& output ):  
Input: activity name  
Output: activity cluster’s center activity

ActivitySearchCity(const string& input, string& output):  
Input: latitude, longtitude, result size  
Output: the most popular n(n is result size) activities in the scope of the latitude and longitude

ActivitySearchUser(const string& input, string& output):  
Input: activity name  
Output: users’ Id who participated in that activity

WeiboSearchByActivity(const string& input, string& output):  
Input: activity name  
Output: weibo instance of that activity
