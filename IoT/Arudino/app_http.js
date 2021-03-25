const http = require("http");

const server = http.createServer((req, res) => {
    if (req.url === "/") {
        res.write("<h1>Hello from node.js</h1");
    } else {
        res.write(`<h1>You have entered this url : ${req.url}</h1>`);
    }
    res.end();
});

server.listen(3000, () => {
    console.log("The serer is listening on port 3000");
});