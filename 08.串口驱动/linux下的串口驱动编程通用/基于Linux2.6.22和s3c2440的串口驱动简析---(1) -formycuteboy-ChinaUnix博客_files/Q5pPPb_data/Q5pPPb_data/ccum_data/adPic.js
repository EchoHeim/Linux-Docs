function simpleTpl(a,d){var c=function(m,l){if(l){c.$$=c.$$||new Function(c.$);return c.$$.apply(m)}else{var j,h=[],g=[];for(j in m){h.push(j);g.push(m[j])}return(new Function(h,c.$)).apply(m,g)}};if(!c.$){c.$='var $="";';var f=a.replace(/[\r\t\n]/g," ").split("%%"),b=0;while(b<f.length){var e=f[b];if(b%2){c.$+="$+="+e+";"}else{c.$+="$+='"+e+"';"}b++}c.$+="return $;";}return d?c(d):c}var CookieAds={getNowTime:function(){var d=new Date(),f=d.getFullYear(),g=d.getMonth()+1,c=d.getDate(),b=d.getHours(),h=d.getMinutes(),e=d.getSeconds(),a="";a=f+"-"+g+"-"+c+" "+b+":"+h+":"+e;return a},enabled:function(b){var a=false,c=this;if(typeof(c.get(b))==="string"){a=true;return a}return a},set:function(c,d,b){var b=b||{};b.domain=b.domain||"";b.path=b.path||"/";b.expires=b.expires||3600000*24*365;if(typeof b.expires=="number"){var a=new Date();a.setTime(a.getTime()+b.expires)}document.cookie=c+"="+d+";expires="+a.toGMTString()+(b.domain?";domain="+b.domain:"")+";path="+b.path},get:function(a){var d=encodeURIComponent(a)+"=",c=document.cookie.indexOf(d),e=null,b;if(c>-1){b=document.cookie.indexOf(";",c);if(b==-1){b=document.cookie.length}e=decodeURIComponent(document.cookie.substring(c+d.length,b))}return e},remove:function(a){this.set(a,"",{expires:-3600})},uuid:function(){function a(){var f={},e=window,d=e.navigator,g="toLowerCase",i=e.screen,h=document;f.D=i?i.width+"x"+i.height:"-";f.C=i?i.colorDepth+"-bit":"-";f.language=(d&&(d.language||d.browserLanguage)||"-")[g]();f.javaEnabled=d&&d.javaEnabled()?1:0;f.characterSet=h.characterSet||h.charset||"-";return f}function c(){return Math.round(Math.random()*2147483647)}function b(){for(var e=a(),d=window.navigator,e=d.appName+d.version+e.language+d.platform+d.userAgent+e.javaEnabled+e.D+e.C+(document.cookie?document.cookie:"")+(document.referrer?document.referrer:""),d=e.length,f=window.history.length;f>0;){e+=f--^d++}}return c()^b()&2147483647},initjda:function(a){var b=this;if(!b.enabled("__jda")){var e,f,c;f=Date.parse(new Date()).toString().substring(0,10);e="."+b.uuid()+"."+f+"."+f+"."+f+".0";b.set("__jda",e,{expires:180*24*3600000,domain:".jd.com"})}}};CookieAds.initjda();function adPic(g,b,j,a,d,e,i,l,k,c){var f="";var b=b.indexOf("%")>0?b:b+"px";var j=j.indexOf("%")>0?j:j+"px";if(g==2){f='<div style="position:relative;width:%%width%%;height: %%height%%">			  			<div style="overflow:hidden;position: absolute; left: 0; top: 0; z-index: 2;">			   				<object id="jdad" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="%%width%%" height="%%height%%" type="application/x-shockwave-flash">			        		<param name="movie" value="%%src%%">			    				<param name="wmode" value="transparent">			    				<param name="Quality" value="High">			    				<param name="Scale" value="ShowAll">			    				<param name="AllowNetworking" value="all">			    				<param name="AllowFullScreen" value="false">			    				<embed id="jdad" width="%%width%%" height="%%height%%" src="%%src%%" quality="High" pluginspage="http://www.macromedia.com/go/getflashplayer" type="application/x-shockwave-flash" wmode="transparent">			    			</object>			  			</div>			        	<a href="%%ad_link%%" target="_blank" style="position: absolute; top: 0px; left: 0px; z-index:3" >			        		<img src="http://img10.360buyimg.com/da/jfs/t265/312/423396392/49/96a9210a/53eb1eabN9a8b38ae.gif" width="%%width%%" height="%%height%%" border="0">			        	</a>					</div>			  		<img id="tracker_banner%%rid%%" width="0" height="0" border="0" src="%%pos0%%" >'}else{f='<img id="tracker_banner%%rid%%" width="0" height="0" border="0" src="%%pos0%%" style="position: absolute; top: 0px; left: 0px;display:none;">					<div id="jd_banner%%rid%%" style="width: %%width%%; height: %%height%%; position: relative;">					   <script>					     var jsJd = "%%jsJd%%";					     if(jsJd == 1) {					       document.write(\\\'<div class="j_bottomlogo jd_paipai"><a href="%%j_logo_url%%" target="_blank">拍拍推广</a></div>\\\');					     } else {					       document.write(\\\'<div class="j_bottomlogo"><a href="%%j_logo_url%%" target="_blank">京东推广</a></div>\\\');					     }					   <\/script>					   <div style="position:absolute;top:0px;left:0px;width:100%;height:100%;">					     <a href="%%ad_link%%" target="_blank" style"text-align:center" style="display:block;width:100%;height:100%;">					       <img src="%%src%%" height="100%" border="0">					     </a>					   </div>					</div>'}var h=simpleTpl(f,{width:b,height:j,src:a,jsJd:d,ad_link:e,pos0:i,j_logo_url:l,rid:k});document.write(h);if(c&&c.indexOf("%%")<0){document.write('<img width="0" height= "0" src="'+c+'"/>')}};