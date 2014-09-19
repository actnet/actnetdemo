function initialize(act_name) {
    // 初始化地图
    map = new BMap.Map("container");
    var point = new BMap.Point(104.3542, 34.0083);
    map.centerAndZoom(point, 5);
    map.enableScrollWheelZoom();
    map.addControl(new BMap.NavigationControl());
    map.addControl(new BMap.ScaleControl());
    map.addControl(new BMap.MapTypeControl());

    document.title = act_name;
    encoded_act_name = encodeURIComponent(act_name);
    //alert(encoded_act_name);

    $.getJSON("/queryall?q="+act_name, function(data) {
        // 请求基础数据
        // 绘制坐标点
        // $.each(data['result']['query']['Points'], function(index, element) {
        //     var point = new BMap.Point(element['lng'], element['lat']);
        //     addMarker(map, point, index, "flag");
        // });
        $.getJSON("/query?q="+act_name, function(emotion) {
            // 请求情感数据
            emotionData = emotion;
            // 绘制情感地图
            // renderSentMap(map, emotion['result']);
            // 绘制热力图
            renderHeatMap(map, emotion['result']);
        });
        // 绘制右边栏
        $.each(data['result']['realted'], function(index, element) {
            addRelatedAct(element['Word']);
        });
        // 绘制POI图
        poiDataBuk = data['result']['query']['Summary']['POIType'];
        drawPoiBar(data['result']['query']['Summary']['POIType']);
        // 绘制时间图
        hourDataBuk = data['result']['query']['Summary']['Hour'];
        drawHourBar(data['result']['query']['Summary']['Hour']);
        // 绘制下个活动
        $.each(data['result']['query']['Summary']['Next'], function(key, val) {
            addNextAct(key, val);
        });
        // 绘制子活动情感
        renderEmotion(data['result']['realted']);
        // 绘制全屏图
        drawPoiBarLarge(poiDataBuk);
        drawHourBarLarge(hourDataBuk);
    });

    $.getJSON("/user?q="+act_name, function(users) {
        // 请求用户数据
        // 绘制相关用户
        $.each(users['result'], function(index, element) {
            addRelatedUser(element);
        });
    });
}

function addRelatedAct(activity) {
    var element = "<input type=\"button\" value=\""
        + activity
        + "\" onclick=\"window.location='/activity/"
        + activity
        + "';\" />";
    $("#ul-right-side-bar").append(element);
}

function comparePOI(a, b) {
    if (a["label"] == "其他") {
        return -1;
    } else if (b["label"] == "其他") {
        return 1;
    }

    if (a["value"] < b["value"]) {
        return -1;
    } else if (a["value"] > b["value"]) {
        return 1;
    } else {
        return 0;
    }
}

function drawPoiBar(raw) {
    var data = [];
    $.each(raw, function(key, val) {
        data.push({"label": key, "value": val});
    });
    data.sort(comparePOI);
    data.reverse();
    var poiData = [{key: "POI Type", values: data}];

    nv.addGraph(function() {
        var chart = nv.models.discreteBarChart()
                .x(function(d) { return d.label })    //Specify the data accessors.
                .y(function(d) { return d.value })
                .staggerLabels(true)    //Too many bars and not enough room? Try staggering labels.
                .tooltips(false)         //Don't show tooltips
                .showValues(true)        //...instead, show the bar value right on top of each bar.
                .transitionDuration(350);

        d3.select('#chart-poi')
            .datum(poiData)
            .call(chart);

        nv.utils.windowResize(chart.update);

        return chart;
    });
}

function drawPoiBarLarge(raw) {
    var data = [];
    $.each(raw, function(key, val) {
        data.push({"label": key, "value": val});
    });
    data.sort(comparePOI);
    data.reverse();
    var poiData = [{key: "POI Type", values: data}];

    nv.addGraph(function() {
        var chart = nv.models.discreteBarChart()
            .x(function(d) { return d.label })    //Specify the data accessors.
            .y(function(d) { return d.value })
            .staggerLabels(false)    //Too many bars and not enough room? Try staggering labels.
            .tooltips(false)         //Don't show tooltips
            .showValues(true)        //...instead, show the bar value right on top of each bar.
            .transitionDuration(350);

        d3.select('#chart-poi-l')
            .datum(poiData)
            .call(chart);

        nv.utils.windowResize(chart.update);

        return chart;
    });
}

function drawHourBar(raw) {
    var entry = [];
    var color = [];
    var numbs = Array.apply(null, Array(24)).map(function (_, i) {
        if (typeof raw[i] == 'undefined') {
            entry.push(0);
        } else {
            entry.push(raw[i]);
        }
        if (i <= 8 || i > 20) {
            color.push("blue");
        } else {
            color.push("green");
        }
        return i;
    });
    var rose = new RGraph.Rose('cvs', entry)
        .set('margin', 5)
        .set('labels', numbs)
        .set('colors', color)
        .set('colors.sequential', true)
        .set('text.size', 10)
        .set('labels.axes', '')
        .draw();
}

function drawHourBarLarge(raw) {
    var entry = [];
    var color = [];
    var numbs = Array.apply(null, Array(24)).map(function (_, i) {
        if (typeof raw[i] == 'undefined') {
            entry.push(0);
        } else {
            entry.push(raw[i]);
        }
        if (i <= 8 || i > 20) {
            color.push("blue");
        } else {
            color.push("green");
        }
        return i;
    });
    var rose = new RGraph.Rose('cvs-l', entry)
        .set('margin', 5)
        .set('labels', numbs)
        .set('colors', color)
        .set('colors.sequential', true)
        .set('text.size', 10)
        .set('labels.axes', '')
        .draw();
}

function addNextAct(key, num) {
    var element = "<li><div class=\"next-act-info\"><span class=\"next-act-name\"><a href=\"/activity/"
        + key + "\">" + key + "</a></span><span class=\"next-act-num\">"
        + num.toFixed(4) + "</span></div></li>";
    if ($("#next-act-ul").children().length < 3) {
        $("#next-act-ul").append(element);
    } else {
        $("#next-act-ul-right").append(element);
    }
}

function addRelatedUser(obj) {
    var element = "<li><div class=\"user-info\"><div class=\"portrait\"><img src=\""
        + obj["src"] + "\" alt=\"\"/></div>"
        + "<div class=\"name\"><span>"
        + obj["name"] + "</span></div></div></li>";
    if ($("#related-user-ul").children().length < 3) {
        $("#related-user-ul").append(element);
    } else {
        $("#related-user-ul-right").append(element);
    }
}

function inChina(lng, lat) {
    if (lat > 4 && lat < 54 && lng < 153 && lng > 73)
        return true;
    return false;
}

function renderHeatMap(map, raw) {
    var points = [];
    $.each(raw, function(index, element) {
        if (inChina(element["lng"], element["lat"])) {
            points.push({"lng": element["lng"], "lat": element["lat"], "count": 1});
        }
    });

    heatmapOverlay = new BMapLib.HeatmapOverlay({"radius": 4});
    map.addOverlay(heatmapOverlay);
    heatmapOverlay.setDataSet({data: points,max: 1});
    // heatmapOverlay.toggle();
}

function addMarker(map, point, index, sentiment) {
    var myIcon = new BMap.Icon("images/" + sentiment + ".png", new BMap.Size(16, 16), {
        // 指定定位位置。
        // 当标注显示在地图上时，其所指向的地理位置距离图标左上
        // 角各偏移10像素和25像素。您可以看到在本例中该位置即是
        // 图标中央下端的尖角位置。
        offset: new BMap.Size(8, 8),
        // 设置图片偏移。
        // 当您需要从一幅较大的图片中截取某部分作为标注图标时，您
        // 需要指定大图的偏移位置，此做法与css sprites技术类似。
        imageOffset: new BMap.Size(0, 0)
        // 设置图片偏移
    });
    // 创建标注对象并添加到地图
    var marker = new BMap.Marker(point, {icon: myIcon});
    map.addOverlay(marker);
}

function clearOverlays() {
    map.clearOverlays();
}

function renderSentMap(map, raw) {
    $.each(raw, function(index, element) {
         if (inChina(element["lng"], element["lat"])) {
             var point = new BMap.Point(element['lng'], element['lat']);
             addMarker(map, point, index, element['sentiment']);
         }
    });
}

function renderEmotion(raw) {
    $.each(raw, function(index, val) {
        if (index < 3) {
            var lit = $("#sub-acts-box-ul li:nth-child(" + (index + 1).toString() +")");
            lit.find("a").text(val["Word"]);
            lit.find("a").attr("href", "/activity/" + val["Word"]);
            lit.find("span.pos-percent").text((val["Sim"].toFixed(2) * 100).toFixed(0).toString()+"%");
            lit.find("span.neg-percent").text((100 - val["Sim"].toFixed(2) * 100).toFixed(0).toString()+"%");
            lit.css("visibility","visible");
        } else if (index < 6) {
            var lit = $("#sub-acts-box-ul-right li:nth-child(" + (index - 2).toString() +")");
            lit.find("a").text(val["Word"]);
            lit.find("a").attr("href", "/activity/" + val["Word"]);
            lit.find("span.pos-percent").text((val["Sim"].toFixed(2) * 100).toFixed(0).toString()+"%");
            lit.find("span.neg-percent").text((100 - val["Sim"].toFixed(2) * 100).toFixed(0).toString()+"%");
            lit.css("visibility", "visible");
        }
    });
}

function hideBigPics() {
    $("#full").css("visibility", "hidden");
    $("#chart-poi-l").css("height", "0px");
    $("#cvs-l").css("height", "0px");
}

function getVisitCount()
{
    $.getJSON("/visitcount", function(data) {
        $("#bottom_count").html("IP访问数: " + data["result"]);
    });
}

