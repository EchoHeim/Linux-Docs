function getCookie(objName) {
    debugger;

    var arrStr = document.cookie.split("; ");

    for (var i = 0; i < arrStr.length; i++) {

        var temp = arrStr[i].split("=");

        if (temp[0] == objName) {

            return temp[1];
        }
    }
}
//===============（返回顶部）begin==================//
var w = 45;     //bubuko提示：离右侧距离
var h = 110;    //bubuko提示：离底部距离

var wW = document.body.clientWidth;     //bubuko提示：获得当前页面宽度
if (wW > 1000)                          //bubuko提示：页面宽度大于1000时贴在内容旁边
    w = (wW - 1000) / 2 - 5;

var str = "";
var obj = document.getElementById("divStayTopLeft");
if (obj) str = obj.innerHTML;
if (typeof document.compatMode != 'undefined' && document.compatMode != 'BackCompat') {
    document.writeln('<DIV  style="z-index:9;right:0;bottom:0;height:' + h + 'px;width:' + w + 'px;overflow:hidden;POSITION:fixed;_position:absolute; _margin-top:expression(document.documentElement.clientHeight-this.style.pixelHeight+document.documentElement.scrollTop);">');
}
else {
    document.writeln('<DIV  style="z-index:9;right:0;bottom:0;height:' + h + 'px;width:' + w + 'px;overflow:hidden;POSITION:fixed;*position:absolute; *top:expression(eval(document.body.scrollTop)+eval(document.body.clientHeight)-this.style.pixelHeight);">');
}
document.writeln('<div style="clear:both;margin:auto;height:180px;overflow:hidden;font-weight:bold;text-align:left;">');
document.writeln('<a href="javascript:scroll(0,0)" hidefocus="true" style="text-decoration:none;"><div style="text-align:center;width:20px;border:1px #e1e1e1 solid;  padding:6px 6px 6px 6px;font-weight:bold;font-size:20px;border-radius:20px;-webkit-border-radius:20px;-moz-border-radius:20px;">↑</div></a>');
document.writeln('<a href="javascript:scroll(0,document.body.scrollHeight)" hidefocus="true" style="text-decoration:none;"><div style="text-align:center;width:20px;border:1px #e1e1e1 solid; padding:6px 6px 6px 6px;margin-top:10px;font-weight:bold;font-size:20px;border-radius:20px;-webkit-border-radius:20px;-moz-border-radius:20px;">↓</div></a></div> ');
document.write('<div style="clear:both;margin:auto;overflow:hidden;text-align:left;">' + str + '</div>');
document.writeln('</DIV>');
//===============（返回顶部）end===================//
//===============（菜单栏选中处理）begin==================//
var _url = window.location.href;
if (_url.length < 25)
    document.getElementById("bubukoindex").className = "title0c";
if (_url.indexOf("info.html") > 0)
    document.getElementById("infohtml").className = "title0c";
if (_url.indexOf("infolist-2") > 0 || _url.indexOf("infotoplist-2") > 0)
    document.getElementById("infolist-2").className = "title1c";
if (_url.indexOf("infolist-3") > 0 || _url.indexOf("infotoplist-3") > 0)
    document.getElementById("infolist-3").className = "title1c";
if (_url.indexOf("infolist-4") > 0 || _url.indexOf("infotoplist-4") > 0)
    document.getElementById("infolist-4").className = "title1c";
if (_url.indexOf("infolist-5") > 0 || _url.indexOf("infotoplist-5") > 0)
    document.getElementById("infolist-5").className = "title1c";
if (_url.indexOf("infolist-6") > 0 || _url.indexOf("infotoplist-6") > 0)
    document.getElementById("infolist-6").className = "title1c";
if (_url.indexOf("infolist-7") > 0 || _url.indexOf("infotoplist-7") > 0)
    document.getElementById("infolist-7").className = "title1c";
if (_url.indexOf("infolist-8") > 0 || _url.indexOf("infotoplist-8") > 0)
    document.getElementById("infolist-8").className = "title1c";
if (_url.indexOf("infolist-9") > 0 || _url.indexOf("infotoplist-9") > 0)
    document.getElementById("infolist-9").className = "title1c";
if (_url.indexOf("infolist-10") > 0 || _url.indexOf("infotoplist-10") > 0)
    document.getElementById("infolist-10").className = "title1c";
if (_url.indexOf("infolist-11") > 0 || _url.indexOf("infotoplist-11") > 0)
    document.getElementById("infolist-11").className = "title1c";
if (_url.indexOf("infolist-12") > 0 || _url.indexOf("infotoplist-12") > 0)
    document.getElementById("infolist-12").className = "title1c";
if (_url.indexOf("analysis") > 0 || _url.indexOf("analysis-") > 0)
    document.getElementById("infolist-12").className = "title1c";

if (_url.indexOf("member.html") > 0)
    document.getElementById("memberhtml").className = "title1c";
if (_url.indexOf("member-page-") > 0)
    document.getElementById("memberhtml").className = "title1c";
if (_url.indexOf("favorite.html") > 0)
    document.getElementById("favoritehtml").className = "title1c";
if (_url.indexOf("favorite-") > 0)
    document.getElementById("favoritehtml").className = "title1c";
if (_url.indexOf("so.html") > 0)
    document.getElementById("sohtml").className = "title1c";
if (_url.indexOf("about.html") > 0)
    document.getElementById("abouthtml").className = "title1c";


if (_url.substring(_url.length-6)=="/news/")
    document.getElementById("news/").className = "title0c";
if (_url.indexOf("/news/list-1-") > 0)
    document.getElementById("news/list-1-").className = "title1c";
if (_url.indexOf("/news/list-2-") > 0)
    document.getElementById("news/list-2-").className = "title1c";
if (_url.indexOf("/news/list-3-") > 0)
    document.getElementById("news/list-3-").className = "title1c";
if (_url.indexOf("/news/list-4-") > 0)
    document.getElementById("news/list-4-").className = "title1c";
if (_url.indexOf("/news/list-5-") > 0)
    document.getElementById("news/list-5-").className = "title1c";
if (_url.indexOf("/news/list-6-") > 0)
    document.getElementById("news/list-6-").className = "title1c";
if (_url.indexOf("/news/list-7-") > 0)
    document.getElementById("news/list-7-").className = "title1c";
if (_url.indexOf("/news/list-8-") > 0)
    document.getElementById("news/list-8-").className = "title1c";
if (_url.indexOf("/news/list-9-") > 0)
    document.getElementById("news/list-9-").className = "title1c";
if (_url.indexOf("/news/list-10-") > 0)
    document.getElementById("news/list-10-").className = "title1c";
if (_url.indexOf("/news/list-11-") > 0)
    document.getElementById("news/list-11-").className = "title1c";
if (_url.indexOf("/news/list-12-") > 0)
    document.getElementById("news/list-12-").className = "title1c";
if (_url.indexOf("/news/list-13-") > 0)
    document.getElementById("news/list-13-").className = "title1c";
//===============（菜单栏选中处理）end===================//

//------（登录状态）begin--------//
$.ajax({
    type: "POST", cache: false,
    url: "/ajaxjs/member_login.aspx?act=loginstate",
    data: "",
    success: function (data) {
        if (data != null && data != "") {
            $("#logintopdescription").html(data);
        }
    }
});
//------（登录状态）end--------//

//------（百度分享）begin--------//
window._bd_share_config = { "common": { "bdSnsKey": {}, "bdText": "", "bdMini": "2", "bdMiniList": false, "bdPic": "", "bdStyle": "0", "bdSize": "16" }, "slide": { "type": "slide", "bdImg": "0", "bdPos": "right", "bdTop": "58.5" }, "image": { "viewList": ["qzone", "tsina", "tqq", "renren", "weixin"], "viewText": "分享到：", "viewSize": "32" }, "selectShare": { "bdContainerClass": null, "bdSelectMiniList": ["qzone", "tsina", "tqq", "renren", "weixin"]} }; with (document) 0[(getElementsByTagName('head')[0] || body).appendChild(createElement('script')).src = 'http://bdimg.share.baidu.com/static/api/js/share.js?v=89860593.js?cdnversion=' + ~(-new Date() / 36e5)];
//------（百度分享）end--------//

(function ($) {
    var obj = $("#xuanting");
    if (obj) {
        var left = parseInt(($(document).width() - 1000) / 2) + 1000 - 300;
        var contentTop = parseInt(obj.offset().top);
        $(window).bind("scroll", function () {
            var tt = $(document).scrollTop() - 1;
            if (tt > contentTop && $(document).height() > 3800) {
                obj.css("position", "fixed");
                obj.css("left", "" + left + "px");
                obj.css("top", "1px");
                obj.css("z-index", "1000000");
            }
            if (tt <= contentTop) {
                obj.css("position", "");
            }
        });
    }
})(jQuery);