(window.webpackJsonp=window.webpackJsonp||[]).push([[327,100,114,115,120,122,145],{1186:function(e,t,r){var content=r(1201);content.__esModule&&(content=content.default),"string"==typeof content&&(content=[[e.i,content,""]]),content.locals&&(e.exports=content.locals);(0,r(36).default)("4e7cb2af",content,!0,{sourceMap:!1})},1196:function(e,t,r){"use strict";r.r(t);var n=r(8),component=Object(n.a)({},(function(){return(0,this._self._c)("div",{staticClass:"w-full animate-pulse rounded-md bg-gray-200"},[this._t("default")],2)}),[],!1,null,null,null);t.default=component.exports},1198:function(e,t,r){"use strict";r.r(t);var n={name:"Section",props:{title:{type:String,default:""},titleFontSize:{type:String,default:"text-2xl"},titleFontWeight:{type:String,default:"font-bold"},viewAllTitle:{type:String,default:"Tümü"},viewAllUrl:{type:String,default:""},customClass:{type:[String,Array,Object],default:null}}},o=r(8),component=Object(o.a)(n,(function(){var e=this,t=e._self._c;return t("BaseContainer",{attrs:{"custom-class":["mb-10",e.customClass]}},[e.title||e.viewAllUrl?t("div",{class:["flex items-center pb-4",e.title?"justify-between":"justify-end"]},[e.title?t("BaseHeading",{staticClass:"text-gray-600",attrs:{tag:"h3",size:e.titleFontSize,font:e.titleFontWeight}},[e._v("\n      "+e._s(e.title)+"\n    ")]):e._e(),e._v(" "),e.viewAllUrl?t("BaseLink",{attrs:{to:e.viewAllUrl,"font-size":"text-sm",color:"text-gray-500"}},[e._v("\n      "+e._s(e.viewAllTitle)+"\n    ")]):e._e()],1):e._e(),e._v(" "),e._t("default")],2)}),[],!1,null,null,null);t.default=component.exports;installComponents(component,{BaseHeading:r(114).default,BaseLink:r(63).default,BaseContainer:r(87).default})},1200:function(e,t,r){"use strict";r(1186)},1201:function(e,t,r){var n=r(35)((function(i){return i[1]}));n.push([e.i,".swiper-button-next[data-v-1df79abd],.swiper-button-prev[data-v-1df79abd]{--tw-border-opacity:1;--tw-bg-opacity:1;--tw-shadow:0 1px 3px 0 rgba(0,0,0,.1),0 1px 2px -1px rgba(0,0,0,.1);--tw-shadow-colored:0 1px 3px 0 var(--tw-shadow-color),0 1px 2px -1px var(--tw-shadow-color);--swiper-navigation-size:36px;background-color:#fff;border-color:#f5f5f5;border-radius:.375rem;border-width:1px;box-shadow:0 0 transparent,0 0 transparent,0 1px 3px 0 rgba(0,0,0,.1),0 1px 2px -1px rgba(0,0,0,.1);box-shadow:var(--tw-ring-offset-shadow,0 0 #0000),var(--tw-ring-shadow,0 0 #0000),var(--tw-shadow);height:2.25rem!important;padding:.563rem;width:2.25rem!important}@supports (color:rgb(0 0 0/0)) and (top:var(--f )){.swiper-button-next[data-v-1df79abd],.swiper-button-prev[data-v-1df79abd]{background-color:rgb(255 255 255/var(--tw-bg-opacity));border-color:rgb(245 245 245/var(--tw-border-opacity))}}.swiper-button-prev[data-v-1df79abd]{left:-.5rem}.swiper-button-next[data-v-1df79abd]{right:-.5rem}",""]),n.locals={},e.exports=n},1205:function(e,t,r){"use strict";r.r(t);var n=r(2),o=(r(28),r(59),r(272),r(37)),l={name:"NavOutside",props:{gradientPanel:{type:Boolean,default:!1},customClass:{type:[Array,Object,String],default:null},slideClass:{type:[Array,Object,String],default:null},swiperData:{type:Array,default:function(){return[]}},slideKey:{type:String,default:""},slidesPerView:{type:[Number,String],default:5},slidesPerGroup:{type:Number,default:5},selectedIndex:{type:Number,default:0},activeCategoryId:{type:String,default:null}},data:function(){var e=this;return{swiperSlideWidth:null,virtualItemData:{slides:[]},swiperOptions:{slidesPerView:this.slidesPerView,slidesPerGroup:this.slidesPerGroup,speed:400,resistanceRatio:.01,virtual:"auto"!==this.slidesPerView&&{slides:this.swiperData,renderExternal:function(data){e.virtualItemData=data}}},showPrev:!1,showNext:!1}},computed:{swiper:function(){var e;return null===(e=this.$refs.swiperRef)||void 0===e?void 0:e.$swiper}},watch:{selectedIndex:function(e){var t=e-2;this.swiper.slideTo(t)}},created:function(){this.virtualItemData.slides=this.swiperData},methods:{showNavHandler:function(){this.showPrev=!this.swiper.isBeginning,this.showNext=!this.swiper.isEnd},swiperReady:function(){var e=this;return Object(n.a)(regeneratorRuntime.mark((function t(){var r,n,o;return regeneratorRuntime.wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return t.next=2,e.$nextTick();case 2:e.swiper&&(e.swiper.update(),e.showNavHandler(),e.swiperSlideWidth=null===(r=e.$refs.swiperRef.$el.querySelector(".swiper-slide"))||void 0===r?void 0:r.offsetWidth,e.activeCategoryId&&(o=(null===(n=e.swiperData)||void 0===n?void 0:n.findIndex((function(t){return t.id===e.activeCategoryId})))||0,e.swiper.slideTo(o-2)));case 3:case"end":return t.stop()}}),t)})))()},getRandomId:function(){return o.a.uuidv4()}}},c=(r(1200),r(8)),component=Object(c.a)(l,(function(){var e=this,t=e._self._c;return t("div",{staticClass:"relative",class:e.customClass},[t("keep-alive",[t("Swiper",{ref:"swiperRef",attrs:{options:e.swiperOptions,"auto-destroy":!1,"auto-update":!1},on:{"touch-start":e.showNavHandler,"transition-start":e.showNavHandler,ready:e.swiperReady}},e._l(e.virtualItemData.slides,(function(r,n){return t("SwiperSlide",{key:e.slideKey?r[e.slideKey]+"-"+e.getRandomId():n,class:e.slideClass,style:{left:e.virtualItemData.offset&&"".concat(e.virtualItemData.offset,"px"),width:e.swiperSlideWidth&&"".concat(e.swiperSlideWidth,"px")}},[e._t("default",null,{item:r,index:n})],2)})),1)],1),e._v(" "),e.showPrev?t("BaseSvg",{attrs:{file:"arrow-angle-left",color:"!text-gray-600","custom-class":"swiper-button-prev !z-30"},on:{click:function(t){return e.swiper.slidePrev()}}}):e._e(),e._v(" "),e.showNext?t("BaseSvg",{attrs:{file:"arrow-angle-right",color:"!text-gray-600","custom-class":"swiper-button-next !z-30"},on:{click:function(t){return e.swiper.slideNext()}}}):e._e(),e._v(" "),!e.showNext&&e.gradientPanel?t("div",{staticClass:"w-16 h-full absolute top-0 left-0 z-20 bg-gradient-to-r from-white to-[rgba(255,255,255,0)]"}):e._e(),e._v(" "),e.showNext&&e.gradientPanel?t("div",{staticClass:"w-16 h-full absolute top-0 right-0 z-20 bg-gradient-to-r from-[rgba(255,255,255,0)] to-white"}):e._e()],1)}),[],!1,null,"1df79abd",null);t.default=component.exports;installComponents(component,{BaseSvg:r(74).default})},1214:function(e,t,r){var content=r(1248);content.__esModule&&(content=content.default),"string"==typeof content&&(content=[[e.i,content,""]]),content.locals&&(e.exports=content.locals);(0,r(36).default)("67efaab6",content,!0,{sourceMap:!1})},1247:function(e,t,r){"use strict";r(1214)},1248:function(e,t,r){var n=r(35)((function(i){return i[1]}));n.push([e.i,".slide-enter-active[data-v-28ad0a5a],.slide-leave-active[data-v-28ad0a5a]{transition:all .3s ease}.slide-enter[data-v-28ad0a5a],.slide-leave-to[data-v-28ad0a5a]{transform:translateY(100%)}",""]),n.locals={},e.exports=n},1255:function(e,t,r){"use strict";r.r(t);r(92);var n={name:"ScrollToTop",data:function(){return{timer:0,st:0,wh:0}},mounted:function(){this.wh=window.innerHeight,window.addEventListener("scroll",this.handleScroll)},beforeDestroy:function(){window.removeEventListener("scroll",this.handleScroll)},methods:{handleScroll:function(){var e=this;clearTimeout(this.timer),this.timer=setTimeout((function(){e.st=window.scrollY}),50)},smoothScroll:function(e){var t=this,r=Date.now();!function n(){var o=Date.now()-r,l=e;o<500&&(l=window.pageYOffset+(e-window.pageYOffset)*t.easeInOutCubic(o/500),requestAnimationFrame(n)),window.scrollTo(0,l)}()},easeInOutCubic:function(e){return e<.5?4*e*e*e:(e-1)*(2*e-2)*(2*e-2)+1}}},o=(r(1247),r(8)),component=Object(o.a)(n,(function(){var e=this,t=e._self._c;return t("transition",{attrs:{name:"slide"}},[e.st>e.wh?t("div",{staticClass:"fixed z-50 bottom-0 right-1/2 mr-[-615px] pb-10"},[t("BaseButton",{staticClass:"bg-white rounded-full shadow-md px-4",attrs:{outline:"","custom-text-class":"!mr-3","after-icon-name":"short-arrow-up","after-icon-color":"text-gray-300"},on:{click:function(t){return e.smoothScroll(0)}}},[e._v("\n      Yukarı Çık\n    ")])],1):e._e()])}),[],!1,null,"28ad0a5a",null);t.default=component.exports;installComponents(component,{BaseButton:r(55).default})},1256:function(e,t,r){"use strict";var n=r(23),o=r(570),l=r(81),c=r(78),d=r(110),f=r(224);n({target:"Array",proto:!0},{flat:function(){var e=arguments.length?arguments[0]:void 0,t=l(this),r=c(t),n=f(t,0);return n.length=o(n,t,t,r,0,void 0===e?1:d(e)),n}})},1257:function(e,t,r){r(196)("flat")},1316:function(e,t,r){"use strict";r.r(t);var n=r(8),component=Object(n.a)({},(function(){var e=this,t=e._self._c;return t("div",{staticClass:"border rounded-md border-gray-200"},[t("div",{staticClass:"flex h-56 items-center justify-center"},[t("BaseSvg",{attrs:{file:"pazarama-skeleton-logo"}})],1),e._v(" "),t("div",{staticClass:"py-3 px-5 grid justify-items-center"},[t("BaseSkeleton",{staticClass:"h-3 mb-2"}),e._v(" "),t("BaseSkeleton",{staticClass:"h-3 mb-8"}),e._v(" "),t("BaseSkeleton",{staticClass:"h-7 !w-32 !rounded-lg mb-2"})],1)])}),[],!1,null,null,null);t.default=component.exports;installComponents(component,{BaseSvg:r(74).default,BaseSkeleton:r(1196).default})},1526:function(e,t,r){"use strict";r.r(t);var n=r(50),o=(r(11),r(56),{name:"HomeInfiniteScrollSkeleton",data:function(){return{productListCount:Object(n.a)(Array(5).keys())}}}),l=r(8),component=Object(l.a)(o,(function(){var e=this,t=e._self._c;return t("div",[t("BaseSkeleton",{staticClass:"!w-60 h-6 !rounded-3xl mb-3"}),e._v(" "),t("BaseSwiperNavOutside",{attrs:{"custom-class":"-mx-3.75","slide-class":"!w-1/5 p-2.5","swiper-data":e.productListCount}},[t("BaseProductCardSkeletonForHome")],1)],1)}),[],!1,null,null,null);t.default=component.exports;installComponents(component,{BaseSkeleton:r(1196).default,BaseProductCardSkeletonForHome:r(1316).default,BaseSwiperNavOutside:r(1205).default})},1711:function(e,t,r){"use strict";r.r(t);r(19),r(21),r(25),r(22),r(26);var n=r(0),o=r(2),l=(r(28),r(11),r(53),r(56),r(20),r(100),r(40),r(52),r(75),r(1256),r(1257),r(13)),c=r(1),d=r(61);function f(object,e){var t=Object.keys(object);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(object);e&&(r=r.filter((function(e){return Object.getOwnPropertyDescriptor(object,e).enumerable}))),t.push.apply(t,r)}return t}function v(e){for(var i=1;i<arguments.length;i++){var source=null!=arguments[i]?arguments[i]:{};i%2?f(Object(source),!0).forEach((function(t){Object(n.a)(e,t,source[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(source)):f(Object(source)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(source,t))}))}return e}var m={name:"HomePage",mixins:[{head:function(){return{title:this.$config.CAPITALIZED_SITE_URL+" - Online Alışveriş Sitesi",meta:[{hid:"description",name:"description",content:"Elektronik, moda, ev dekorasyon, kırtasiye ofis ve diğer tüm kategorilerde milyonlarca ürün seçeneğinin yer aldığı hızlı ve güvenli alışveriş sitesi."}],script:[{type:"application/ld+json",json:{"@context":"http://schema.org","@type":"BreadcrumbList",itemListElement:[{"@type":"ListItem",position:1,name:"Anasayfa",item:this.$config.CANONICAL_HOMEPAGE_URL}]}}]}}}],scrollToTop:!0,asyncData:function(e){return Object(o.a)(regeneratorRuntime.mark((function t(){var r,n,o,param,l,d;return regeneratorRuntime.wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return r=e.store,n=e.error,o=e.$config,param={bannerLocationType:1,pageSize:10,pageIndex:1},t.prev=2,l=[r.dispatch(Object(c.oe)(c.F),{param:param,infinite:!1}),r.dispatch(Object(c.oe)(c.G),{seoUrl:o.HOMEPAGE_URL+o.HOME_CATEGORY_BANNER_URL}),r.dispatch(Object(c.oe)(c.H))],t.next=6,Promise.all(l);case 6:t.next=11;break;case 8:t.prev=8,t.t0=t.catch(2),n({statusCode:(null===t.t0||void 0===t.t0||null===(d=t.t0.response)||void 0===d?void 0:d.status)||500});case 11:case"end":return t.stop()}}),t,null,[[2,8]])})))()},data:function(){return{baseHeroComponent:"1",baseHeroSideComponent:"32",param:{bannerLocationType:1,pageSize:10,pageIndex:1},categoryBannerMainSize:d.a.HOME_CATEGORY_BANNER_MAIN,categoryBannerThumbnailSize:d.a.HOME_CATEGORY_BANNER_THUMBNAIL,categoryBannerHeroSideCardSize:d.a.HOME_CATEGORY_BANNER_HERO_SIDE_CARD}},computed:v(v({},Object(l.c)({getHomeBannerList:Object(c.oe)(c.zb),getHomeCategoryBannerList:Object(c.oe)(c.Ab),homeReadyPage:Object(c.oe)(c.Bb),isInfiniteLoading:Object(c.oe)(c.Db),getCategoryHyerarchyList:Object(c.oe)(c.nb)})),{},{mainBannerList:function(){var e=this;return this.getHomeBannerList.filter((function(t){return t.cardType!==e.baseHeroSideComponent}))},heroSideBannerList:function(){var e,t=this;return null===(e=this.getHomeBannerList.find((function(e){return e.cardType===t.baseHeroSideComponent})))||void 0===e?void 0:e.itemList}}),mounted:function(){this.setHomePageReady(!0),this.categoryHyerarchy()},created:function(){var e=this.$cookiz.get("logout-redirect");e&&e.includes("uyelik-iptal")&&this.$router.push(e)},methods:v(v(v({},Object(l.d)({setHomePageReady:Object(c.oe)(c.xd)})),Object(l.b)({fetchBannerList:Object(c.oe)(c.F),fetchCategoryHyerarchy:Object(c.oe)(c.v)})),{},{infiniteHandler:function(e){var t=this;return Object(o.a)(regeneratorRuntime.mark((function r(){return regeneratorRuntime.wrap((function(r){for(;;)switch(r.prev=r.next){case 0:return t.param.pageIndex+=1,r.prev=1,r.next=4,t.fetchBannerList({param:t.param,infinite:!0});case 4:e.loaded(),r.next=10;break;case 7:r.prev=7,r.t0=r.catch(1),e.complete();case 10:case"end":return r.stop()}}),r,null,[[1,7]])})))()},getCategoryHyerarchy:function(e){var t=this;return Object(o.a)(regeneratorRuntime.mark((function r(){return regeneratorRuntime.wrap((function(r){for(;;)switch(r.prev=r.next){case 0:return r.next=2,t.fetchCategoryHyerarchy(e);case 2:case"end":return r.stop()}}),r)})))()},categoryHyerarchy:function(){var e=this;return Object(o.a)(regeneratorRuntime.mark((function t(){var r,n;return regeneratorRuntime.wrap((function(t){for(;;)switch(t.prev=t.next){case 0:return r=e.mainBannerList.map((function(i){return i.itemList})).flat().map((function(e){return{productId:e.productId,sellerId:e.sellerId}})),n={sellerList:r.filter((function(e){return e.productId&&e.sellerId}))},t.next=4,e.getCategoryHyerarchy(n);case 4:case"end":return t.stop()}}),t)})))()}})},h=r(8),component=Object(h.a)(m,(function(){var e=this,t=e._self._c;return t("div",{staticClass:"pt-7"},[t("BaseSection",[t("BaseCategoryBanner",{attrs:{"category-list":e.getHomeCategoryBannerList,"hero-side-banner-list":e.heroSideBannerList,"main-resize":e.categoryBannerMainSize,"thumbnail-resize":e.categoryBannerThumbnailSize,"hero-side-card-resize":e.categoryBannerHeroSideCardSize}})],1),e._v(" "),e._l(e.mainBannerList,(function(r,n){return t("BaseSection",{key:n,attrs:{title:r.title,"title-font-size":r.titleFontSize,"view-all-url":r.seoUrl}},[t(r.componentName,{tag:"component",attrs:{"item-list":r.itemList,layout:r.layout,"card-type":r.cardType,"section-title":r.title,"section-index":n,"category-list":r.hyerarchyList?e.getCategoryHyerarchyList:void 0,resize:r.resize?r.resize:void 0}})],1)})),e._v(" "),e.isInfiniteLoading?t("BaseSection",[t("HomeInfiniteScrollSkeleton")],1):e._e(),e._v(" "),e._e(),e._v(" "),t("BaseScrollToTop"),e._v(" "),t("client-only",[t("infinite-loading",{ref:"infiniteLoading",attrs:{spinner:"spiral",distance:2e3},on:{infinite:e.infiniteHandler},scopedSlots:e._u([{key:"error",fn:function(r){var n=r.trigger;return t("div",{},[e._v("\n        Bir hata oluştu, tekrar denemek için\n        "),t("a",{staticClass:"underline",attrs:{href:"javascript:;"},on:{click:n}},[e._v("buraya")]),e._v(" tıklayın.\n      ")])}}])},[t("div",{attrs:{slot:"no-more"},slot:"no-more"}),e._v(" "),t("div",{attrs:{slot:"no-results"},slot:"no-results"})])],1)],2)}),[],!1,null,null,null);t.default=component.exports;installComponents(component,{BaseCategoryBanner:r(1698).default,BaseSection:r(1198).default,HomeInfiniteScrollSkeleton:r(1526).default,HomeTextSection:r(1699).default,BaseScrollToTop:r(1255).default})}}]);