/*! For license information please see ../LICENSES */
(window.webpackJsonp=window.webpackJsonp||[]).push([[334],{1246:function(t,e,r){"use strict";Object.defineProperty(e,"__esModule",{value:!0});var n=["area","base","br","col","command","embed","hr","img","input","keygen","link","meta","param","source","track","wbr"],o=["address","article","aside","blockquote","canvas","dd","div","dl","dt","fieldset","figcaption","figure","footer","form","h1","h2","h3","h4","h5","h6","header","hgroup","hr","li","main","nav","noscript","ol","output","p","pre","section","table","tbody","tfoot","thead","tr","ul","video"],c=["audio","math","svg","video"],l=10,f=33,h=34,d=38,m=39,w=47,v=59,C=60,y=61,S=62,T=/[<&\n\ud800-\udbff]/,k=/[<&\ud800-\udbff]/,_=/\s+/g;function I(t,e){for(var r=t.length,i=e;i<r;i++)if(j(t.charCodeAt(i)))return i;return r}function E(t){return t>=48&&t<=57||t>=65&&t<=90||t>=97&&t<=122}function M(t,e){var r=t.charCodeAt(e);if(r===l)return!0;if(r===C){var n="("+o.join("|")+"|br)";return new RegExp("^<"+n+"[\t\n\f\r ]*/?>","i").test(t.slice(e))}return!1}function j(t){return 9===t||10===t||12===t||13===t||32===t}function A(t){for(var i=t.length-1;i>=0;i--){var e=t[i];if("li"===e||"td"===e)return!1;if("ol"===e||"table"===e||"ul"===e)return!0}return!1}function P(t){return t.trim().replace(_," ")}function O(t,e){var r=t.charCodeAt(e);if(55296==(64512&r)){var n=t.charCodeAt(e+1);if(56320==(64512&n))return String.fromCharCode(r,n)}return String.fromCharCode(r)}e.default=function(t,e,r){return void 0===r&&(r={}),t?(t=t.toString(),r.html?function(t,e,r){for(var _=r.imageWeight,D=void 0===_?2:_,F=r.indicator,L=void 0===F?"…":F,x=r.maxLines,N=void 0===x?1/0:x,$=r.stripTags,B=void 0!==$&&$,K=L.length,R=1,V="boolean"==typeof B?function(){return B}:function(t){return B.includes(t)},z=[],H=function(t){for(var e;void 0!==(e=z.pop());)V(e)||(t+="</"+e+">");return t},i=0,U=-1,W=t.length;i<W;i++){var J=i?t.slice(i):t,G=A(z),Y=U>-1||G?k:T,Q=J.search(Y),X=Q>-1?Q:J.length;if(-1===U)if(G){var Z=P(X===J.length?J:J.slice(0,Q));if(V(z[z.length-1])){var tt=i>0&&!j(t.charCodeAt(i-1)),et=!j(t.charCodeAt(i+X));Z.length>0?Z=(tt?" ":"")+Z+(et?" ":""):tt&&et&&(Z=" "),t=t.slice(0,i)+Z+t.slice(i+X),X=Z.length}if((K+=Z.length)>e)break}else if((K+=X)>e){i=Math.max(i+X-K+e,0);break}if(i+=X,-1===Q)break;if((Tt=t.charCodeAt(i))===C){var it=(mt=t.charCodeAt(i+1))===f;if(it&&"--"===t.substr(i+2,2))i=t.indexOf("--\x3e",i+4)+3-1;else if(it&&"[CDATA["===t.substr(i+2,7)){i=t.indexOf("]]>",i+9)+3-1}else{var nt=mt===w;if(K===e&&!nt){K++;break}for(var at=0,st=i,ot=!1;;){if(++st>=W)throw new Error("Invalid HTML: "+t);var ct=t.charCodeAt(st);if(ot)at?ct===at&&(ot=!1):j(ct)?ot=!1:ct===S&&(ot=!1,st--);else if(ct===y){for(;j(t.charCodeAt(st+1));)st++;ot=!0;var ut=t.charCodeAt(st+1);ut===h||ut===m?(at=ut,st++):at=0}else if(ct===S){var lt=i+(nt?2:1),ft=Math.min(I(t,lt),st);(Ct=t.slice(lt,ft).toLowerCase()).charCodeAt(Ct.length-1)===w&&(Ct=Ct.slice(0,Ct.length-1));var gt=V(Ct);if(nt){if(z.pop()!==Ct)throw new Error("Invalid HTML: "+t);if(c.includes(Ct))if(c.some((function(t){return z.includes(t)})));else if(gt)i=U,U=-1;else if(U=-1,(K+=D)>e)break;if(o.includes(Ct)&&-1===U&&!gt&&++R>N){z.push(Ct);break}}else if(n.includes(Ct)||t.charCodeAt(st-1)===w){if(gt);else if("br"===Ct){if(++R>N)break}else if("img"===Ct&&(K+=D)>e)break}else c.some((function(t){return z.includes(t)}))||c.includes(Ct)&&(U=i),z.push(Ct);gt&&-1===U?(t=t.slice(0,i)+t.slice(st+1),i--):i=st;break}}if(K>e||R>N)break}}else if(Tt===d){st=i+1;for(var ht=!0;;){var pt=t.charCodeAt(st);if(!E(pt)){if(pt===v)break;ht=!1;break}st++}if(-1===U&&++K>e)break;ht&&(i=st)}else if(Tt===l){if(++K>e)break;if(++R>N)break}else{if(-1===U&&++K>e)break;var mt;if(55296==(64512&Tt))56320==(64512&(mt=t.charCodeAt(i+1)))&&i++}}if(K>e){var wt=function(t,e){var r=O(t,e);if("&"===r)for(;;){e++;var n=t.charCodeAt(e);if(!E(n)){if(n===v){r+=String.fromCharCode(n);break}break}r+=String.fromCharCode(n)}return r}(t,i);if(L){for(var vt=i+wt.length;t.charCodeAt(vt)===C&&t.charCodeAt(vt+1)===w;){var bt=t.indexOf(">",vt+2)+1;if(!bt)break;vt=bt}vt&&(vt===t.length||M(t,vt))&&(i+=wt.length,wt=t.charAt(i))}for(;"<"===wt&&t.charCodeAt(i+1)===w;){var Ct;if(!(Ct=z.pop()))break;var yt=t.indexOf(">",i+2);if(-1===yt||t.slice(i+2,yt).trim()!==Ct)throw new Error("Invalid HTML: "+t);V(Ct)?t=t.slice(0,i)+t.slice(yt+1):i=yt+1,wt=t.charAt(i)}if(i<t.length){if(!r.breakWords)for(var St=i-L.length;St>=0;St--){var Tt;if((Tt=t.charCodeAt(St))===S||Tt===v)break;if(Tt===l||Tt===C){i=St;break}if(j(Tt)){i=St+(L?1:0);break}}var kt=t.slice(0,i);return M(t,i)||(kt+=L),H(kt)}}else if(R>N)return H(t.slice(0,i));return t}(t,e,r):function(t,e,r){for(var n=r.indicator,o=void 0===n?"…":n,c=r.maxLines,f=void 0===c?1/0:c,h=o.length,d=1,i=0,m=t.length;i<m&&!(++h>e);i++){if((y=t.charCodeAt(i))===l){if(++d>f)break}else if(55296==(64512&y)){56320==(64512&t.charCodeAt(i+1))&&i++}}if(h>e){var w=O(t,i);if(o){var v=i+w.length;if(v===t.length)return t;if(t.charCodeAt(v)===l)return t.slice(0,i+w.length)}if(!r.breakWords)for(var C=i-o.length;C>=0;C--){var y;if((y=t.charCodeAt(C))===l){i=C,w="\n";break}if(j(y)){i=C+(o?1:0);break}}return t.slice(0,i)+("\n"===w?"":o)}if(d>f)return t.slice(0,i);return t}(t,e,r)):""}},1705:function(t,e,r){"use strict";r.d(e,"a",(function(){return Jt})),r.d(e,"b",(function(){return xt})),r.d(e,"c",(function(){return $t}));var n=r(1290),o=r(1249),c=r(1270),l=r(1302);const f=(object,t)=>t.some((t=>object instanceof t));let h,d;const m=new WeakMap,w=new WeakMap,v=new WeakMap,C=new WeakMap,y=new WeakMap;let S={get(t,e,r){if(t instanceof IDBTransaction){if("done"===e)return w.get(t);if("objectStoreNames"===e)return t.objectStoreNames||v.get(t);if("store"===e)return r.objectStoreNames[1]?void 0:r.objectStore(r.objectStoreNames[0])}return _(t[e])},set:(t,e,r)=>(t[e]=r,!0),has:(t,e)=>t instanceof IDBTransaction&&("done"===e||"store"===e)||e in t};function T(t){return t!==IDBDatabase.prototype.transaction||"objectStoreNames"in IDBTransaction.prototype?(d||(d=[IDBCursor.prototype.advance,IDBCursor.prototype.continue,IDBCursor.prototype.continuePrimaryKey])).includes(t)?function(...e){return t.apply(I(this),e),_(m.get(this))}:function(...e){return _(t.apply(I(this),e))}:function(e,...r){const n=t.call(I(this),e,...r);return v.set(n,e.sort?e.sort():[e]),_(n)}}function k(t){return"function"==typeof t?T(t):(t instanceof IDBTransaction&&function(t){if(w.has(t))return;const e=new Promise(((e,r)=>{const n=()=>{t.removeEventListener("complete",o),t.removeEventListener("error",c),t.removeEventListener("abort",c)},o=()=>{e(),n()},c=()=>{r(t.error||new DOMException("AbortError","AbortError")),n()};t.addEventListener("complete",o),t.addEventListener("error",c),t.addEventListener("abort",c)}));w.set(t,e)}(t),f(t,h||(h=[IDBDatabase,IDBObjectStore,IDBIndex,IDBCursor,IDBTransaction]))?new Proxy(t,S):t)}function _(t){if(t instanceof IDBRequest)return function(t){const e=new Promise(((e,r)=>{const n=()=>{t.removeEventListener("success",o),t.removeEventListener("error",c)},o=()=>{e(_(t.result)),n()},c=()=>{r(t.error),n()};t.addEventListener("success",o),t.addEventListener("error",c)}));return e.then((e=>{e instanceof IDBCursor&&m.set(e,t)})).catch((()=>{})),y.set(e,t),e}(t);if(C.has(t))return C.get(t);const e=k(t);return e!==t&&(C.set(t,e),y.set(e,t)),e}const I=t=>y.get(t);const E=["get","getKey","getAll","getAllKeys","count"],M=["put","add","delete","clear"],j=new Map;function A(t,e){if(!(t instanceof IDBDatabase)||e in t||"string"!=typeof e)return;if(j.get(e))return j.get(e);const r=e.replace(/FromIndex$/,""),n=e!==r,o=M.includes(r);if(!(r in(n?IDBIndex:IDBObjectStore).prototype)||!o&&!E.includes(r))return;const c=async function(t,...e){const c=this.transaction(t,o?"readwrite":"readonly");let l=c.store;return n&&(l=l.index(e.shift())),(await Promise.all([l[r](...e),o&&c.done]))[0]};return j.set(e,c),c}S=(t=>({...t,get:(e,r,n)=>A(e,r)||t.get(e,r,n),has:(e,r)=>!!A(e,r)||t.has(e,r)}))(S);const P="@firebase/installations",O="0.6.4",D=1e4,F=`w:${O}`,L="FIS_v2",x="https://firebaseinstallations.googleapis.com/v1",N=36e5,$={"missing-app-config-values":'Missing App configuration value: "{$valueName}"',"not-registered":"Firebase Installation is not registered.","installation-not-found":"Firebase Installation not found.","request-failed":'{$requestName} request failed with error "{$serverCode} {$serverStatus}: {$serverMessage}"',"app-offline":"Could not process request. Application offline.","delete-pending-registration":"Can't delete installation while there is a pending registration request."},B=new o.b("installations","Installations",$);function K(t){return t instanceof o.c&&t.code.includes("request-failed")}function R({projectId:t}){return`${x}/projects/${t}/installations`}function V(t){return{token:t.token,requestStatus:2,expiresIn:(e=t.expiresIn,Number(e.replace("s","000"))),creationTime:Date.now()};var e}async function z(t,e){const r=(await e.json()).error;return B.create("request-failed",{requestName:t,serverCode:r.code,serverMessage:r.message,serverStatus:r.status})}function H({apiKey:t}){return new Headers({"Content-Type":"application/json",Accept:"application/json","x-goog-api-key":t})}function U(t,{refreshToken:e}){const r=H(t);return r.append("Authorization",function(t){return`${L} ${t}`}(e)),r}async function W(t){const e=await t();return e.status>=500&&e.status<600?t():e}function J(t){return new Promise((e=>{setTimeout(e,t)}))}const G=/^[cdef][\w-]{21}$/,Y="";function Q(){try{const t=new Uint8Array(17);(self.crypto||self.msCrypto).getRandomValues(t),t[0]=112+t[0]%16;const e=function(t){const e=(r=t,btoa(String.fromCharCode(...r)).replace(/\+/g,"-").replace(/\//g,"_"));var r;return e.substr(0,22)}(t);return G.test(e)?e:Y}catch(t){return Y}}function X(t){return`${t.appName}!${t.appId}`}const Z=new Map;function tt(t,e){const r=X(t);et(r,e),function(t,e){const r=nt();r&&r.postMessage({key:t,fid:e});at()}(r,e)}function et(t,e){const r=Z.get(t);if(r)for(const t of r)t(e)}let it=null;function nt(){return!it&&"BroadcastChannel"in self&&(it=new BroadcastChannel("[Firebase] FID Change"),it.onmessage=t=>{et(t.data.key,t.data.fid)}),it}function at(){0===Z.size&&it&&(it.close(),it=null)}const st="firebase-installations-database",ot=1,ct="firebase-installations-store";let ut=null;function lt(){return ut||(ut=function(t,e,{blocked:r,upgrade:n,blocking:o,terminated:c}={}){const l=indexedDB.open(t,e),f=_(l);return n&&l.addEventListener("upgradeneeded",(t=>{n(_(l.result),t.oldVersion,t.newVersion,_(l.transaction))})),r&&l.addEventListener("blocked",(()=>r())),f.then((t=>{c&&t.addEventListener("close",(()=>c())),o&&t.addEventListener("versionchange",(()=>o()))})).catch((()=>{})),f}(st,ot,{upgrade:(t,e)=>{if(0===e)t.createObjectStore(ct)}})),ut}async function ft(t,e){const r=X(t),n=(await lt()).transaction(ct,"readwrite"),o=n.objectStore(ct),c=await o.get(r);return await o.put(e,r),await n.done,c&&c.fid===e.fid||tt(t,e.fid),e}async function gt(t){const e=X(t),r=(await lt()).transaction(ct,"readwrite");await r.objectStore(ct).delete(e),await r.done}async function ht(t,e){const r=X(t),n=(await lt()).transaction(ct,"readwrite"),o=n.objectStore(ct),c=await o.get(r),l=e(c);return void 0===l?await o.delete(r):await o.put(l,r),await n.done,!l||c&&c.fid===l.fid||tt(t,l.fid),l}async function pt(t){let e;const r=await ht(t.appConfig,(r=>{const n=function(t){const e=t||{fid:Q(),registrationStatus:0};return vt(e)}(r),o=function(t,e){if(0===e.registrationStatus){if(!navigator.onLine){return{installationEntry:e,registrationPromise:Promise.reject(B.create("app-offline"))}}const r={fid:e.fid,registrationStatus:1,registrationTime:Date.now()},n=async function(t,e){try{const r=await async function({appConfig:t,heartbeatServiceProvider:e},{fid:r}){const n=R(t),o=H(t),c=e.getImmediate({optional:!0});if(c){const t=await c.getHeartbeatsHeader();t&&o.append("x-firebase-client",t)}const body={fid:r,authVersion:L,appId:t.appId,sdkVersion:F},l={method:"POST",headers:o,body:JSON.stringify(body)},f=await W((()=>fetch(n,l)));if(f.ok){const t=await f.json();return{fid:t.fid||r,registrationStatus:2,refreshToken:t.refreshToken,authToken:V(t.authToken)}}throw await z("Create Installation",f)}(t,e);return ft(t.appConfig,r)}catch(r){throw K(r)&&409===r.customData.serverCode?await gt(t.appConfig):await ft(t.appConfig,{fid:e.fid,registrationStatus:0}),r}}(t,r);return{installationEntry:r,registrationPromise:n}}return 1===e.registrationStatus?{installationEntry:e,registrationPromise:mt(t)}:{installationEntry:e}}(t,n);return e=o.registrationPromise,o.installationEntry}));return r.fid===Y?{installationEntry:await e}:{installationEntry:r,registrationPromise:e}}async function mt(t){let e=await wt(t.appConfig);for(;1===e.registrationStatus;)await J(100),e=await wt(t.appConfig);if(0===e.registrationStatus){const{installationEntry:e,registrationPromise:r}=await pt(t);return r||e}return e}function wt(t){return ht(t,(t=>{if(!t)throw B.create("installation-not-found");return vt(t)}))}function vt(t){return 1===(e=t).registrationStatus&&e.registrationTime+D<Date.now()?{fid:t.fid,registrationStatus:0}:t;var e}async function bt({appConfig:t,heartbeatServiceProvider:e},r){const n=function(t,{fid:e}){return`${R(t)}/${e}/authTokens:generate`}(t,r),o=U(t,r),c=e.getImmediate({optional:!0});if(c){const t=await c.getHeartbeatsHeader();t&&o.append("x-firebase-client",t)}const body={installation:{sdkVersion:F,appId:t.appId}},l={method:"POST",headers:o,body:JSON.stringify(body)},f=await W((()=>fetch(n,l)));if(f.ok){return V(await f.json())}throw await z("Generate Auth Token",f)}async function Ct(t,e=!1){let r;const n=await ht(t.appConfig,(n=>{if(!St(n))throw B.create("not-registered");const o=n.authToken;if(!e&&function(t){return 2===t.requestStatus&&!function(t){const e=Date.now();return e<t.creationTime||t.creationTime+t.expiresIn<e+N}(t)}(o))return n;if(1===o.requestStatus)return r=async function(t,e){let r=await yt(t.appConfig);for(;1===r.authToken.requestStatus;)await J(100),r=await yt(t.appConfig);const n=r.authToken;return 0===n.requestStatus?Ct(t,e):n}(t,e),n;{if(!navigator.onLine)throw B.create("app-offline");const e=function(t){const e={requestStatus:1,requestTime:Date.now()};return Object.assign(Object.assign({},t),{authToken:e})}(n);return r=async function(t,e){try{const r=await bt(t,e),n=Object.assign(Object.assign({},e),{authToken:r});return await ft(t.appConfig,n),r}catch(r){if(!K(r)||401!==r.customData.serverCode&&404!==r.customData.serverCode){const r=Object.assign(Object.assign({},e),{authToken:{requestStatus:0}});await ft(t.appConfig,r)}else await gt(t.appConfig);throw r}}(t,e),e}}));return r?await r:n.authToken}function yt(t){return ht(t,(t=>{if(!St(t))throw B.create("not-registered");const e=t.authToken;return 1===(r=e).requestStatus&&r.requestTime+D<Date.now()?Object.assign(Object.assign({},t),{authToken:{requestStatus:0}}):t;var r}))}function St(t){return void 0!==t&&2===t.registrationStatus}async function Tt(t,e=!1){const r=t;await async function(t){const{registrationPromise:e}=await pt(t);e&&await e}(r);return(await Ct(r,e)).token}function kt(t){return B.create("missing-app-config-values",{valueName:t})}const _t="installations",It=t=>{const e=t.getProvider("app").getImmediate(),r=function(t){if(!t||!t.options)throw kt("App Configuration");if(!t.name)throw kt("App Name");const e=["projectId","apiKey","appId"];for(const r of e)if(!t.options[r])throw kt(r);return{appName:t.name,projectId:t.options.projectId,apiKey:t.options.apiKey,appId:t.options.appId}}(e);return{app:e,appConfig:r,heartbeatServiceProvider:Object(n._getProvider)(e,"heartbeat"),_delete:()=>Promise.resolve()}},Et=t=>{const e=t.getProvider("app").getImmediate(),r=Object(n._getProvider)(e,_t).getImmediate();return{getId:()=>async function(t){const e=t,{installationEntry:r,registrationPromise:n}=await pt(e);return n?n.catch(console.error):Ct(e).catch(console.error),r.fid}(r),getToken:t=>Tt(r,t)}};Object(n._registerComponent)(new c.a(_t,It,"PUBLIC")),Object(n._registerComponent)(new c.a("installations-internal",Et,"PRIVATE")),Object(n.registerVersion)(P,O),Object(n.registerVersion)(P,O,"esm2017");const Mt="@firebase/remote-config",jt="0.4.4";class At{constructor(){this.listeners=[]}addEventListener(t){this.listeners.push(t)}abort(){this.listeners.forEach((t=>t()))}}const Pt="remote-config",Ot={"registration-window":"Undefined window object. This SDK only supports usage in a browser environment.","registration-project-id":"Undefined project identifier. Check Firebase app initialization.","registration-api-key":"Undefined API key. Check Firebase app initialization.","registration-app-id":"Undefined app identifier. Check Firebase app initialization.","storage-open":"Error thrown when opening storage. Original error: {$originalErrorMessage}.","storage-get":"Error thrown when reading from storage. Original error: {$originalErrorMessage}.","storage-set":"Error thrown when writing to storage. Original error: {$originalErrorMessage}.","storage-delete":"Error thrown when deleting from storage. Original error: {$originalErrorMessage}.","fetch-client-network":"Fetch client failed to connect to a network. Check Internet connection. Original error: {$originalErrorMessage}.","fetch-timeout":'The config fetch request timed out.  Configure timeout using "fetchTimeoutMillis" SDK setting.',"fetch-throttle":'The config fetch request timed out while in an exponential backoff state. Configure timeout using "fetchTimeoutMillis" SDK setting. Unix timestamp in milliseconds when fetch request throttling ends: {$throttleEndTimeMillis}.',"fetch-client-parse":"Fetch client could not parse response. Original error: {$originalErrorMessage}.","fetch-status":"Fetch server returned an HTTP error status. HTTP status: {$httpStatus}.","indexed-db-unavailable":"Indexed DB is not supported by current browser"},Dt=new o.b("remoteconfig","Remote Config",Ot);const Ft=["1","true","t","yes","y","on"];class Lt{constructor(t,e=""){this._source=t,this._value=e}asString(){return this._value}asBoolean(){return"static"!==this._source&&Ft.indexOf(this._value.toLowerCase())>=0}asNumber(){if("static"===this._source)return 0;let t=Number(this._value);return isNaN(t)&&(t=0),t}getSource(){return this._source}}function xt(t=Object(n.getApp)()){t=Object(o.o)(t);return Object(n._getProvider)(t,Pt).getImmediate()}async function Nt(t){const e=Object(o.o)(t),r=new At;setTimeout((async()=>{r.abort()}),e.settings.fetchTimeoutMillis);try{await e._client.fetch({cacheMaxAgeMillis:e.settings.minimumFetchIntervalMillis,signal:r}),await e._storageCache.setLastFetchStatus("success")}catch(t){const r=function(t,e){return t instanceof o.c&&-1!==t.code.indexOf(e)}(t,"fetch-throttle")?"throttle":"failure";throw await e._storageCache.setLastFetchStatus(r),t}}function $t(t,e){const r=Object(o.o)(t);r._isInitializationComplete||r._logger.debug(`A value was requested for key "${e}" before SDK initialization completed. Await on ensureInitialized if the intent was to get a previously activated value.`);const n=r._storageCache.getActiveConfig();return n&&void 0!==n[e]?new Lt("remote",n[e]):r.defaultConfig&&void 0!==r.defaultConfig[e]?new Lt("default",String(r.defaultConfig[e])):(r._logger.debug(`Returning static value for key "${e}". Define a default or remote value if this is unintentional.`),new Lt("static"))}class Bt{constructor(t,e,r,n){this.client=t,this.storage=e,this.storageCache=r,this.logger=n}isCachedDataFresh(t,e){if(!e)return this.logger.debug("Config fetch cache check. Cache unpopulated."),!1;const r=Date.now()-e,n=r<=t;return this.logger.debug(`Config fetch cache check. Cache age millis: ${r}. Cache max age millis (minimumFetchIntervalMillis setting): ${t}. Is cache hit: ${n}.`),n}async fetch(t){const[e,r]=await Promise.all([this.storage.getLastSuccessfulFetchTimestampMillis(),this.storage.getLastSuccessfulFetchResponse()]);if(r&&this.isCachedDataFresh(t.cacheMaxAgeMillis,e))return r;t.eTag=r&&r.eTag;const n=await this.client.fetch(t),o=[this.storageCache.setLastSuccessfulFetchTimestampMillis(Date.now())];return 200===n.status&&o.push(this.storage.setLastSuccessfulFetchResponse(n)),await Promise.all(o),n}}function qt(t=navigator){return t.languages&&t.languages[0]||t.language}class Kt{constructor(t,e,r,n,o,c){this.firebaseInstallations=t,this.sdkVersion=e,this.namespace=r,this.projectId=n,this.apiKey=o,this.appId=c}async fetch(t){const[e,r]=await Promise.all([this.firebaseInstallations.getId(),this.firebaseInstallations.getToken()]),n=`${window.FIREBASE_REMOTE_CONFIG_URL_BASE||"https://firebaseremoteconfig.googleapis.com"}/v1/projects/${this.projectId}/namespaces/${this.namespace}:fetch?key=${this.apiKey}`,o={"Content-Type":"application/json","Content-Encoding":"gzip","If-None-Match":t.eTag||"*"},c={sdk_version:this.sdkVersion,app_instance_id:e,app_instance_id_token:r,app_id:this.appId,language_code:qt()},l={method:"POST",headers:o,body:JSON.stringify(c)},f=fetch(n,l),h=new Promise(((e,r)=>{t.signal.addEventListener((()=>{const t=new Error("The operation was aborted.");t.name="AbortError",r(t)}))}));let d;try{await Promise.race([f,h]),d=await f}catch(t){let e="fetch-client-network";throw"AbortError"===(null==t?void 0:t.name)&&(e="fetch-timeout"),Dt.create(e,{originalErrorMessage:null==t?void 0:t.message})}let m=d.status;const w=d.headers.get("ETag")||void 0;let v,C;if(200===d.status){let t;try{t=await d.json()}catch(t){throw Dt.create("fetch-client-parse",{originalErrorMessage:null==t?void 0:t.message})}v=t.entries,C=t.state}if("INSTANCE_STATE_UNSPECIFIED"===C?m=500:"NO_CHANGE"===C?m=304:"NO_TEMPLATE"!==C&&"EMPTY_CONFIG"!==C||(v={}),304!==m&&200!==m)throw Dt.create("fetch-status",{httpStatus:m});return{status:m,eTag:w,config:v}}}class Rt{constructor(t,e){this.client=t,this.storage=e}async fetch(t){const e=await this.storage.getThrottleMetadata()||{backoffCount:0,throttleEndTimeMillis:Date.now()};return this.attemptFetch(t,e)}async attemptFetch(t,{throttleEndTimeMillis:e,backoffCount:r}){await function(t,e){return new Promise(((r,n)=>{const o=Math.max(e-Date.now(),0),c=setTimeout(r,o);t.addEventListener((()=>{clearTimeout(c),n(Dt.create("fetch-throttle",{throttleEndTimeMillis:e}))}))}))}(t.signal,e);try{const e=await this.client.fetch(t);return await this.storage.deleteThrottleMetadata(),e}catch(e){if(!function(t){if(!(t instanceof o.c&&t.customData))return!1;const e=Number(t.customData.httpStatus);return 429===e||500===e||503===e||504===e}(e))throw e;const n={throttleEndTimeMillis:Date.now()+Object(o.f)(r),backoffCount:r+1};return await this.storage.setThrottleMetadata(n),this.attemptFetch(t,n)}}}class Vt{constructor(t,e,r,n,o){this.app=t,this._client=e,this._storageCache=r,this._storage=n,this._logger=o,this._isInitializationComplete=!1,this.settings={fetchTimeoutMillis:6e4,minimumFetchIntervalMillis:432e5},this.defaultConfig={}}get fetchTimeMillis(){return this._storageCache.getLastSuccessfulFetchTimestampMillis()||-1}get lastFetchStatus(){return this._storageCache.getLastFetchStatus()||"no-fetch-yet"}}function zt(t,e){const r=t.target.error||void 0;return Dt.create(e,{originalErrorMessage:r&&(null==r?void 0:r.message)})}const Ht="app_namespace_store";class Ut{constructor(t,e,r,n=function(){return new Promise(((t,e)=>{try{const r=indexedDB.open("firebase_remote_config",1);r.onerror=t=>{e(zt(t,"storage-open"))},r.onsuccess=e=>{t(e.target.result)},r.onupgradeneeded=t=>{const e=t.target.result;0===t.oldVersion&&e.createObjectStore(Ht,{keyPath:"compositeKey"})}}catch(t){e(Dt.create("storage-open",{originalErrorMessage:null==t?void 0:t.message}))}}))}()){this.appId=t,this.appName=e,this.namespace=r,this.openDbPromise=n}getLastFetchStatus(){return this.get("last_fetch_status")}setLastFetchStatus(t){return this.set("last_fetch_status",t)}getLastSuccessfulFetchTimestampMillis(){return this.get("last_successful_fetch_timestamp_millis")}setLastSuccessfulFetchTimestampMillis(t){return this.set("last_successful_fetch_timestamp_millis",t)}getLastSuccessfulFetchResponse(){return this.get("last_successful_fetch_response")}setLastSuccessfulFetchResponse(t){return this.set("last_successful_fetch_response",t)}getActiveConfig(){return this.get("active_config")}setActiveConfig(t){return this.set("active_config",t)}getActiveConfigEtag(){return this.get("active_config_etag")}setActiveConfigEtag(t){return this.set("active_config_etag",t)}getThrottleMetadata(){return this.get("throttle_metadata")}setThrottleMetadata(t){return this.set("throttle_metadata",t)}deleteThrottleMetadata(){return this.delete("throttle_metadata")}async get(t){const e=await this.openDbPromise;return new Promise(((r,n)=>{const o=e.transaction([Ht],"readonly").objectStore(Ht),c=this.createCompositeKey(t);try{const t=o.get(c);t.onerror=t=>{n(zt(t,"storage-get"))},t.onsuccess=t=>{const e=t.target.result;r(e?e.value:void 0)}}catch(t){n(Dt.create("storage-get",{originalErrorMessage:null==t?void 0:t.message}))}}))}async set(t,e){const r=await this.openDbPromise;return new Promise(((n,o)=>{const c=r.transaction([Ht],"readwrite").objectStore(Ht),l=this.createCompositeKey(t);try{const t=c.put({compositeKey:l,value:e});t.onerror=t=>{o(zt(t,"storage-set"))},t.onsuccess=()=>{n()}}catch(t){o(Dt.create("storage-set",{originalErrorMessage:null==t?void 0:t.message}))}}))}async delete(t){const e=await this.openDbPromise;return new Promise(((r,n)=>{const o=e.transaction([Ht],"readwrite").objectStore(Ht),c=this.createCompositeKey(t);try{const t=o.delete(c);t.onerror=t=>{n(zt(t,"storage-delete"))},t.onsuccess=()=>{r()}}catch(t){n(Dt.create("storage-delete",{originalErrorMessage:null==t?void 0:t.message}))}}))}createCompositeKey(t){return[this.appId,this.appName,this.namespace,t].join()}}class Wt{constructor(t){this.storage=t}getLastFetchStatus(){return this.lastFetchStatus}getLastSuccessfulFetchTimestampMillis(){return this.lastSuccessfulFetchTimestampMillis}getActiveConfig(){return this.activeConfig}async loadFromStorage(){const t=this.storage.getLastFetchStatus(),e=this.storage.getLastSuccessfulFetchTimestampMillis(),r=this.storage.getActiveConfig(),n=await t;n&&(this.lastFetchStatus=n);const o=await e;o&&(this.lastSuccessfulFetchTimestampMillis=o);const c=await r;c&&(this.activeConfig=c)}setLastFetchStatus(t){return this.lastFetchStatus=t,this.storage.setLastFetchStatus(t)}setLastSuccessfulFetchTimestampMillis(t){return this.lastSuccessfulFetchTimestampMillis=t,this.storage.setLastSuccessfulFetchTimestampMillis(t)}setActiveConfig(t){return this.activeConfig=t,this.storage.setActiveConfig(t)}}async function Jt(t){return t=Object(o.o)(t),await Nt(t),async function(t){const e=Object(o.o)(t),[r,n]=await Promise.all([e._storage.getLastSuccessfulFetchResponse(),e._storage.getActiveConfigEtag()]);return!!(r&&r.config&&r.eTag&&r.eTag!==n)&&(await Promise.all([e._storageCache.setActiveConfig(r.config),e._storage.setActiveConfigEtag(r.eTag)]),!0)}(t)}Object(n._registerComponent)(new c.a(Pt,(function(t,{instanceIdentifier:e}){const r=t.getProvider("app").getImmediate(),c=t.getProvider("installations-internal").getImmediate();if("undefined"==typeof window)throw Dt.create("registration-window");if(!Object(o.u)())throw Dt.create("indexed-db-unavailable");const{projectId:f,apiKey:h,appId:d}=r.options;if(!f)throw Dt.create("registration-project-id");if(!h)throw Dt.create("registration-api-key");if(!d)throw Dt.create("registration-app-id");e=e||"firebase";const m=new Ut(d,r.name,e),w=new Wt(m),v=new l.b(Mt);v.logLevel=l.a.ERROR;const C=new Kt(c,n.SDK_VERSION,e,f,h,d),y=new Rt(C,m),S=new Bt(y,m,w,v),T=new Vt(r,S,w,m,v);return function(t){const e=Object(o.o)(t);e._initializePromise||(e._initializePromise=e._storageCache.loadFromStorage().then((()=>{e._isInitializationComplete=!0}))),e._initializePromise}(T),T}),"PUBLIC").setMultipleInstances(!0)),Object(n.registerVersion)(Mt,jt),Object(n.registerVersion)(Mt,jt,"esm2017")}}]);