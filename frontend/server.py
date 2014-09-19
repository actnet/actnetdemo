#!env python2
#encoding: utf8

import os
import os.path
from bottle import route, run, template, view, static_file, request, urlencode, redirect
from saeclient import SAEClient
import logging
import influence_analysis
import influence_analysis_patent
import urllib2
#import sample_data
import time
import re
import json
#import markdown

import sys
reload(sys)
sys.setdefaultencoding('utf8')

logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)
client = SAEClient("tcp://127.0.0.1:40110")

knowledge_drift_clients = {}
def get_knowledge_drift_client(dataset):
    global client
    if dataset not in knowledge_drift_clients:
        knowledge_drift_clients[dataset] = KnowledgeDrift(client, dataset)
    return knowledge_drift_clients[dataset]

logging.info("done")

@route('/')
def index():
    file_object = open('actnet/home.html')
    try:
        all_the_text = file_object.read()
    finally:
        file_object.close()
    return all_the_text

@route('/:filename')
def index(filename):
    file_object = open('actnet/' + filename)
    try:
        all_the_text = file_object.read()
    finally:
        file_object.close()
    return all_the_text

@route('/activity/:filename')
def index(filename):
    file_object = open('actnet/detail.html')
    try:
        all_the_text = file_object.read()
    finally:
        file_object.close()
    return all_the_text

# @route('/visitcount')
# def visitcount():
#     global ip_count
#     try:
#         ip_count = ip_count + 1
#         saveIP('ips.txt', ip_count)
#         return dict(error=None,result=ip_count + 3353)
#     except Exception, e:
#         print Exception, ":", e
#         return dict(error=None,result=ip_count + 3353)


@route('/visitcount')
def visitcount():
    global ip_count
    try:
        ip_count = ip_count + 1
        return dict(error=None,result=ip_count + 4638)
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=4638)

@route('/visit')
def visitcount():
    return dict(result=ips)

@route('/searchall')
def searchall():
    try:
        q = request.query.q or ''
        all_result=client.activit_search_all_by_name(q)
        retList=[]
        cnt=0;
        for users in all_result.users:
            for name in users.ids:
                cnt+=1
                if(cnt>1):
                    break
                retList.append(get_info_by_id(name))
        for activity in all_result.activities:
            return dict(
                error=None,
                result=dict(
                    queryall=dict(
                        query=dict(
                            Name=activity.name,
                            Points=[
                                dict(
                                    lat=point.lat,
                                    lng=point.lng
                                ) for point in activity.points
                            ],
                            Summary=Summary(activity)
                            ),
                        realted=[
                            dict(
                                Word=point.name,
                                Sim=point.sim
                            ) for point in all_result.similars
                        ],
                        statistics=dict(
                            poisize=len(activity.pois),
                            pointsize=len(activity.points),
                            timestamp=len(activity.timestamps),
                            Nextsize=len(activity.nextpoints),
                            total=all_result.total_count,
                            Namearr=[point.name for point in activity.nextpoints]
                            )
                        ),
                    sentiment=[
                            dict(
                                sentiment=instancelist.sen,
                                lat=instancelist.lat,
                                lng=instancelist.lng
                           ) for instancelist in all_result.actlists
                        ],
                    user=retList
                    )
                )
        return dict(
                error=None,
                result=dict(
                    queryall=None,
                    query=None,
                    user=retList
                )
            )
    except Exception, e:
        print Exception, ":", e
        return dict(
                error=None,
                result=dict(
                    queryall=None,
                    query=None,
                    user=retList
                )
            )

@route('/queryall')
def allsearch():
    try:
        q = request.query.q or ''
        print q
        result=client.activity_search_by_name(q)
        related_result=client.similar_search_by_name(q)
        for activity in result.activities:
            return dict(
                error=None,
                result=dict(
                    query=dict(
                        Name=activity.name,
                        Points=[
                            dict(
                                lat=point.lat,
                                lng=point.lng
                            ) for point in activity.points
                        ],
                        Summary=Summary(activity)
                        ),
                    realted=[
                        dict(
                            Word=point.name,
                            Sim=point.sim
                        ) for point in related_result.similars
                    ],
                    statistics=dict(
                        poisize=len(activity.pois),
                        pointsize=len(activity.points),
                        timestamp=len(activity.timestamps),
                        Nextsize=len(activity.nextpoints),
                        total=result.total_count,
                        Namearr=[point.name for point in activity.nextpoints]
                        )
                    )
                )
        return dict(error=None,result=None)
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)

@route('/city')
def citysearch():
    try:
        q = request.query.q or ''
        result=client.activity_search_by_city(q)
        return dict(
            error=None,
            result=[
                    dict(
                        city=city.name,
                        activities=[name for name in city.activity]
                    ) for city in result.cities
                ]
        )
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)

@route('/query')
def sentimentsearch():
    try:
        q = request.query.q or ''
        result=client.instance_search_by_activity(q)
        return dict(
            error=None,
            result=[
                    dict(
                #Instance=[
                 #   dict(
                        sentiment=instancelist.sen,
                        lat=instancelist.lat,
                        lng=instancelist.lng
                   ) for instancelist in result.actlists
                ]
                #Summary=Summary(activity)
            #)
        )
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)

# @route('/related')
# def similarsearch():
#     q = request.query.q or ''
#     result=client.similar_search_by_name(q)
#     return dict(
#         error=None,
#         result=[
#                 dict(
#                     Word=point.name,
#                     Sim=point.sim
#                 ) for point in result.similars
#             ]
#     )

# @route('/statistics')
# def staticsearch():
#     q = request.query.q or ''
#     result=client.activity_search_by_name(q)
#     activity = result.activities[0]
#     return dict(
#         error=None,
#         result=dict(
#             poisize=len(activity.pois),
#             pointsize=len(activity.points),
#             timestamp=len(activity.timestamps),
#             Nextsize=len(activity.nextpoints),
#             total=result.total_count,
#             Namearr=[point.name for point in activity.nextpoints]
#         )
#     )

@route('/user')
def usersearch():
    try:
        q = request.query.q or ''
        result=client.user_search_by_activity(q)
        users = result.users[0]
        retList=[]
        cnt=0;
        for name in users.ids:
            if(userinfo.has_key(name)):
                retList.append(userinfo[name])
                cnt += 1
            if(cnt >= 6):
                break
        return dict(
            error=None,
            result=retList
            #result=[get_info_by_id(name) for name in users.ids]
            #result=[get_info_by_id(users.ids[0])]
        )
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)


@route('/weibo')
def weibosearch():
    try:
        q = request.query.q or ''
        result=client.weibo_search_by_activity(q)
        weibos = result.weibos
        return dict(
            error=None,
            result=[
                    dict(
                        Id=weibo.id,
                        Weibo=weibo.weibo,
                    ) for weibo in weibos
                ]
        )
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)


@route('/center')
def centersearch():
    try:
        q = request.query.q or ''
        result=client.center_search_by_activity(q)
        lists = result.lists[0]
        return dict(
            error=None,
            result=[activity for activity in lists.activities]
        )
    except Exception, e:
        print Exception, ":", e
        return dict(error=None,result=None)

@route('/frontpage')
def front():
    file_object = open('app/main.html')
    try:
        all_the_text = file_object.read()
    finally:
        file_object.close()
    return all_the_text

@route('/js/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/js')

@route('/css/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/css')

@route('/css/images/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/css/images')

@route('/images/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/images')

@route('/activity/images/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/images')

@route('/rgraph/libraries/:filename')
def stat_file(filename):
    curdir = os.path.dirname(os.path.realpath(__file__))
    return static_file(filename, root = curdir + '/actnet/rgraph/libraries')

def Summary(activity):
    summary = {}
    summary["POIType"] = {}
    summary["Hour"] = {}
    summary["Next"] = {}
    try:
        for poi in activity.pois:
            if poi.type=='位置分类' or poi.type=='未知分类':
                continue
            size = summary["POIType"].get(poi.type, -1)
            if size == -1:
                summary["POIType"][poi.type] = 1
            else:
                summary["POIType"][poi.type] = size + 1

        for timestamp in activity.timestamps:
            #print time.ctime(timestamp)
            timeArray = time.localtime(timestamp)
            hour = timeArray[3]
            hour = hour - 8
            if hour < 0:
                hour = hour + 24
            size = summary["Hour"].get(hour, -1)
            if size == -1:
                summary["Hour"][hour] = 1
            else:
                summary["Hour"][hour] = size + 1

        for nextpoint in activity.nextpoints:
            if nextpoint.name == activity.name:
                continue;
            size = summary["Next"].get(nextpoint.name, -1)
            if size == -1:
                summary["Next"][nextpoint.name] = 1
            else:
                summary["Next"][nextpoint.name] = size + 1
        summary["POIType"] = get_top(summary["POIType"], 10)
        summary["Next"] = get_top(summary["Next"], 6)
        count = 0
        for d,x in summary["Next"].items():
            count = count + x
        for d,x in summary["Next"].items():
            summary["Next"][d] = float(x) / float(count)
        return summary
    except Exception, e:
        print Exception, ":", e
        return summary

def get_top(mydict, length):
    try:
        if len(mydict) <= length:
            return mydict
        items=mydict.items()
        backitems=[[v[1],v[0]] for v in items]
        backitems.sort()
        result = {}
        for i in range(len(backitems) - length, len(backitems)):
            result[backitems[i][1]] = backitems[i][0]
        return result
    except Exception, e:
        print Exception, ":", e
        return mydict

def loaduserinfo(path):
    userinfo = {}
    try:
        file_object = open(path)
        list_of_lines = file_object.readlines()
        for line in list_of_lines:
            row = line.split('\t')
            if(len(row) == 3):
                userinfo[row[0]] = {}
                userinfo[row[0]]["name"] = row[1]
                userinfo[row[0]]["src"] = row[2]
        file_object.close()
        print "load info done"
        return userinfo
    except Exception, e:
        print Exception, ":", e
        return userinfo

# def loadIP(path):
#     try:
#         file_object = open(path)
#         line = file_object.readline()
#         return float(line)
#     except Exception, e:
#         print Exception, ":", e
#         return 0

# def saveIP(path, count):
#     file_object = open(path)
#     file_object.writelines(count)

def loadIP(path):
    ips = {}
    try:
        file_object = open(path)
        list_of_lines = file_object.readlines()
        for line in list_of_lines:
            line = line.strip('\n')
            ips[line] = 1
        file_object.close()
        print "load IP done"
        return ips
    except Exception, e:
        print Exception, ":", e
        return ips

def saveIP(path):
    file_object = open(path, 'w')
    for d,x in ips.items():
        file_object.writelines(d + '\n')
    file_object.close()

def get_info_by_id(user_id):
    try:
        flag = 0
        url = "http://weibo.com/u/" + str(user_id)
        headers = {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'}
        req = urllib2.Request(url=url, headers=headers)
        content = urllib2.urlopen(req).read()
        pattern = re.compile(r'<img width="50" height="50" src=".+" alt=".+" class="W_face_radius">')
        context = pattern.findall(content)
        if(len(context) == 0):
            url = "http://weibo.cn/u/" + str(user_id)
            req = urllib2.Request(url=url, headers=headers)
            content = urllib2.urlopen(req).read()
            pattern = re.compile(r'<img src=".+" alt="[\x80-\xff]+" class="por" />')
            context = pattern.findall(content)
            flag = 1
            #print pattern
        if len(context) == 0:
            fileHandle = open (str(user_id)+'.txt', 'a' )
            fileHandle.write (content)
            fileHandle.close()
            return dict(src = '', name = '')
        image = context[0]
        image = image.split('" alt="')[0]
        image = image.split('src="')[1]
        if flag == 1:
            pattern = re.compile(r'<title>.+</title>')
            name = pattern.findall(content)[0]
            name = name.split('>')[1]
            name = name.split('的微博')[0]
        else:
            name = context[0]
            name = name.split('" alt="')[1]
            name = name.split('" class="W_face_radius">')[0]
        return dict(src = image, name = name)
    except Exception, e:
        print Exception, ":", e
        return dict(src = None, name = None)


userinfo = loaduserinfo('userinfo.txt')
#ip_count = loadIP('ips.txt')
ip_count = 0
ips = loadIP('ips.txt')
if len(sys.argv) > 1:
    port = int(sys.argv[1])
else:
    port = 8099

run(server='auto', host='0.0.0.0', port=port, reloader=True, debug=True)
