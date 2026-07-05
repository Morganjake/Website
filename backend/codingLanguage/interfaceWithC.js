const path = require("path");
const { exec } = require("child_process");
const { resolve } = require("dns");


function formatforOutput(output, error) {
    return output.join("<br>") +  "<error>" + error.join("<br>") + "</error>";
}


function formatforVariable(vars) {
    return "{<br>   " + vars.join("<br>   ") + "<br>}";
}


function formatforTokens(tokens, lines) {
    if (!tokens) { return ""; }
    let res = ['<p id="line-number">Line 1: ' + lines[0] + '</p>'];
    let curLine = 1;

    for (let i = 0; i < tokens.length; i += 2) {

        let line = '<p><tokenType> - ' + tokens[i] + ':</tokenType>'
        // Yeah 52 is a magic number, but it represents the length of "line" using the longest token type, and there isn't really a nicer way to simply do it 
        line += " ".repeat(3 + Math.max(52 - line.length, 0)) + '<tokenValue>' + tokens[i + 1] +'</tokenValue></p>';
        res.push(line);

        if (tokens[i] == "EOL Token" && i + 2 < tokens.length) {
            curLine++;
            res.push(['<br><p id="line-number">Line ' + curLine + ': ' + lines[curLine - 1] + '</p>']);
        }
    }
        
    return res.join("");
}

function formatforAst(lines) {
    let res = [];
    for (let i = 0; i < lines.length; i += 3) {
        let line = "<p>";
        
        if (Number(lines[i]) > 0) { line += "<nodeLine>" + "│ ".repeat(Number(lines[i]) - 1) + "├ </nodeLine>";  }
        else if (i != 0) { line += "<br>"; }

        line += "<nodeType>" + lines[i + 1] + ":</nodeType> " + lines[i + 2] + "</p>";
        res.push(line);
    }
    return res.join("");
}


module.exports = {
    
    async interfaceWithC(input) {
        lines = input.split("\n");
        input = input.replace(/\n/g, " ").replace(/"/g, "\\\"").trim();
        let res = "";
        exec(path.join(__dirname,  `main.exe "${input}"`), (err, stdout, stderr) => {

            if (err) {
                console.error(err);
                return;
            }

            res = stdout;
        });

        while (res === "") {
            await new Promise(resolve => setTimeout(resolve, 100))
        }

        res = res.split("\r\n");
        
        parts = [[], [], [], [], []]

        for (let i = 0; i < res.length; i++) {
            if (res[i][0] == "0") { parts[0].push(res[i].slice(1)) }
            else if (res[i][0] == "1") { parts[1].push(res[i].slice(1)) }
            else if (res[i][0] == "2") { parts[2].push(res[i].slice(1)) }
            else if (res[i][0] == "3") { parts[3].push(res[i].slice(1)) }
            else if (res[i][0] == "4") { parts[4].push(res[i].slice(1)) }
        }

        return {
            "Output": formatforOutput(parts[0], parts[2]),
            "Variables": formatforVariable(parts[1]),
            "Tokens": formatforTokens(parts[3], lines),
            "Ast": formatforAst(parts[4])
        };
    }
} 