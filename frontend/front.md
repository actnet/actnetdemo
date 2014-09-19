# Quick Links

[烤鸭](/activity/烤鸭)
[上网](/activity/上网)
[泡茶](/activity/泡茶)
[潜水](/activity/潜水)
[游泳](/activity/游泳)
[过年](/activity/过年)
[看电影](/activity/看电影)
[滑雪](/activity/滑雪)
[练羽毛球](/activity/练羽毛球)

# Intro

I'm experimenting on Weibo data for human daily activity extraction.

    Total Weibo: 399,068,974
    Weibo with Checkin: 6,248,878
    POIs: 261,106
    Vocabulary: 399530
    Activities: 14,184 / 68,520 / 544,712 (classified as activity, more than 5 times, total extracted)

For each Weibo entry, we can have some of the following attributes:

    1. Weibo Text
    2. Timestamp
    3. User Profile
    4. Geo Location if check-in (sparse)
    5. POI if check-in (sparse)

# Experiments


## Activity Extraction

Currently I am using rules for activity discovery. The following rules are currently used:

    1. Verb
    2. Verb + Noun

I have extracted 544,712 activities from 1 and 2.
68,520 of the activties have appeared more than 5 times.

The Weibo text are in Chinese and segmentation is a serious problem, as the text on Weibo are short, full of slang, and strangely formed.

## Features

For an activity:

    1. Text
        a. Verb / Object
        b. Vector of Verb and Object
    2. Temporal
        a. Checkin Timestamp
        b. Attributes: Month, Day, Weekday, Hour, Minute
    3. Spatial
        a. Lat/Lng
        b. POI Name
        c. POI Type

Note that the POI data is quite sparse, one or two magnitude sparser than checkins.

## Classification

Some of the extracted activities are not actually activities. I used a simple binary classifier to identify the real activities. I have labeled several thousands of activities and using SVM light for training and classification.

# Plan

1. Reverse lookup from Geo(POI) and Time
1. Get relations of two activities (same, same category, inclusion, exclusion, follow-up, etc...)
1. Make Building and Querying

# Thoughts

+ An end to end method for extracting activity network from microblogs, so that we don't rely on data other than Weibo?

# Notes

### Fake Place

Some places are for online events, not real world POIs. For example:

    B2094757D56EA2FB4993 星光公益站之韩庚Love·Life

Can we detect it?
