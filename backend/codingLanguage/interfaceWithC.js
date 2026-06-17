const path = require("path");
const { exec } = require("child_process");
const { resolve } = require("dns");


function formatforOutput(output) {
    return output.join("<br>");
}


function formatforVariable(vars) {
    return "{<br>   " + vars.slice(0, -1).join("<br>   ") + "<br>}";
}


function formatforTokens(tokens, lines) {
    let res = ['<p id="line-number">Line 1: ' + lines[0] + '</p>'];
    let curLine = 1;

    for (let i = 0; i < tokens.length; i += 2) {

        let line = '<p><tokenType> - ' + tokens[i] + ':</tokenType>'
        // Yeah 49 is a magic number, but it represents the length of "line" using the longest token type, and there isn't really a nicer way to simply do it 
        line += " ".repeat(3 + Math.max(49 - line.length, 0)) + '<tokenValue>' + tokens[i + 1] +'</tokenValue></p>';
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
        input = input.replace(/\n/g, " ").replace(/"/g, "\\\"");
        let res = "";
        exec(path.join(__dirname, "main.exe " + input), (err, stdout, stderr) => {

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
        
        parts = [[], [], [], []]
        curPart = 0;

        for (let i = 0; i < res.length; i++) {
            if (curPart < 2 && (res[i] == "END OF TOKENS" || res[i] == "END OF AST")) {
                curPart++;
            }
            else {
                if (curPart == 2) {
                    if (res[i][0] == "0") { parts[2].push(res[i].slice(1)) }
                    else { parts[3].push(res[i].slice(1)) }
                }
                else {
                    parts[curPart].push(res[i]);
                }
            }
        }

        return {
            "Output": formatforOutput(parts[2]),
            "Variables": formatforVariable(parts[3]),
            "Tokens": formatforTokens(parts[0], lines),
            "Ast": formatforAst(parts[1])
        };
    }
} 