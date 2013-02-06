{
	"service" : {
		"api" : "http",
		"port" : 8080,
        "ip" : "0.0.0.0"
	},

    "cache" : {
        "backend" : "thread_shared"
    },
	"http" : {
		"script_names" : ["/TatoWiki"]
	},
	"localization" : {
		"messages" : {
			"paths" : [ "../locale" ],
			"domains" : [ "messages" ]
		},
		"locales" : [
            "en_GB.UTF-8",
            "eo.UTF-8",
            "es_ES.UTF-8",
            "de_DE.UTF-8",
            "fr_FR.UTF-8",
            "it_IT.UTF-8",
            "ja_JP.UTF-8",
            "pl_PL.UTF-8",
            "pt_BR.UTF-8",
            "ru_RU.UTF-8",
            "zh_CN.UTF-8",

        ]
	},
    "session" : {
        "expire" : "renew",
        "timeout" : 604800,
        "location" : "server",
        "cookies" : {
            //replace this value by your own domain
            //note: the . at the beginning is important
            //if you want to stay log in between the different language
            //of your wiki
            "domain" : ".sysko.fr" 
        },
        "server" : {
            "storage" : "memory"
        }
    },
	"TatoWiki" : {
        "interfacelangs" : [
            ["en"  , "en_GB.UTF-8", "English"],
            ["de"  , "de_DE.UTF-8", "Deutsh"],
            ["eo"  , "eo.UTF-8", "Esperanto"],
            ["es"  , "es_ES.UTF-8", "Español"],
            ["fr"  , "fr_FR.UTF-8", "Français"],
            ["it"  , "it_IT.UTF-8", "Italiano"],
            ["ja"  , "ja_JP.UTF-8", "日本語"],
            ["pl"  , "pl_PL.UTF-8", "Polski"],
            ["pt"  , "pt_BR.UTF-8", "Português (BR)"],
            ["ru"  , "ru_RU.UTF-8", "Русский"],
            ["zh"  , "zh_CN.UTF-8", "中文"],
            
        ],
        "languages" : [
            ["en" , "English"],
            ["de" , "German"],
            ["eo" , "Esperanto"],
            ["es" , "Spanish"],
            ["fr" , "French"],
            ["it" , "Italian"],
            ["ja" , "Japanese"],
            ["pl" , "Polish"],
            ["pt" , "Portuguese (Brazil)"],
            ["ru" , "Russian"],
            ["zh" , "Mandarin Chinese"],
        ],
        "mainPages" : [
            ["en" , "main"],
            ["de" , "Hauptseite"],
            ["eo" , "ĉefpaĝo"],
            ["es" , "portada"],
            ["fr" , "page-principale"],
            ["it" , "pagina-principale"],
            ["ja" , "メインページ"],
            ["pl" , "strona-główna"],
            ["pt" , "página-principal"],
            ["ru" , "заглавная_страница"],
            ["zh" , "首页"],
        ],
        "sqlite3" : {
            "path" : "../data/sqlite6.db"
        },
        "baseHost" : "sysko.fr:8080",
        "innerCssFolder" : "../resources/css/",
        "innerImgFolder" : "../resources/img/",
        "imgPath" : "/img/",
        "cssPath" : "/css/"
	}
}
