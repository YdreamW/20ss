const express = require("express");
const session = require("express-session");
const cookieParser = require("cookie-parser");
const bodyParser = require("body-parser");
const ejs = require("ejs");

const controller = require("./controller/controller");

const app = express();
app.use(express.static("static"));

//create the server
const server = app.listen(3000, () => {
    console.log("\x1b[32m%s\x1b[0m", "[信息] 聊天室启动于 http://localhost:3000 ");
});

controller.server = server;

app.use(bodyParser.json());
app.use(
    bodyParser.urlencoded({
        extended: false,
    })
);

app.use(cookieParser());
const MemoryStore = session.MemoryStore;
app.use(
    session({
        name: "app.sid",
        secret: "SecureProgrammingLab1@YDream",
        resave: true,
        saveUninitialized: true,
        cookie:
            ("name",
            "value",
            {
                maxAge: 5 * 60 * 1000,
                secure: false,
            }),
    })
);

app.set("view engine", "ejs");

//routers
app.get("/", (req, res) => {
    if (req.session && req.session.account) {
        res.render("chatRoom");
    } else {
        res.render("index");
    }
});

app.post("/login", controller.login);

app.post("/register", controller.register);
app.post("/getchannellist", controller.getChannelList);
app.post("/addchannel", controller.addChannel);
app.post("/addmsg", controller.addMsg);
app.post("/getchat", controller.getChat);
app.post("/changeChannel", controller.changeChannel);
app.post("/logout", controller.logout);

app.get("/chat", (req, res) => {
    res.render("chatRoom");
});
