{
	"service" : {
		"api" : "http",
		"port" : 8080
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
			"domains" : [ "hello" ]
		},
		"locales" : [ "en_GB.UTF-8", "fr_FR.UTF-8" ]
	},
    "session" : {
        "expire" : "renew",
        "timeout" : 604800,
        "location" : "server",
        "server" : {
            "storage" : "memory"
        }
    },
	"TatoWiki" : {
        "interfacelangs" : [
            ["en"  , "en_GB.UTF-8", "English"],
            ["fr"  , "fr_FR.UTF-8", "Français"],
            ["de"  , "de_DE.UTF-8", "Deutsh"]
        ],
        "languages" : [
            ["en" , "English"],
            ["fr" , "French"],
            ["de" , "German"]
        ],
        "mainPages" : [
            ["en" , "main" ],
            ["fr" , "page-principale"],
            ["de" , "main-de"]
        ],
        "sqlite3" : {
            "path" : "../data/sqlite6.db"
        },
        "baseHost" : "tatolocal:8080",
        "innerCssFolder" : "../resources/css/",
        "innerImgFolder" : "../resources/img/",
        "imgPath" : "/img/",
        "cssPath" : "/css/"
	}
}
