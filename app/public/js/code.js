function changeTab(newTab) {
    Array.from(document.getElementsByClassName("tab")).forEach(tab => {
        tab.id = tab.innerHTML == newTab ? "selected" : "";
    });

    Array.from(document.getElementsByClassName("output")).forEach(tab => {
        console.log(tab)
        tab.hidden = tab.id != newTab.toLowerCase() + "-output";
    });
}

const editor = document.getElementById('code-input');
const btn = document.getElementById('submit-button');

const ouputOutput = document.getElementById("output-output")
const variablesOutput = document.getElementById("variables-output")
const tokensOutput = document.getElementById("tokens-output")
const astOutput = document.getElementById("ast-output")

btn.addEventListener("click", async () => {
    btn.disabled = true;
    btn.textContent = "Sending…";
    try {
        const res = await fetch("/api/submit", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ text: editor.value }),
        });

        const data = await res.json();  
        ouputOutput.innerHTML = data.Output
        variablesOutput.innerHTML = data.Variables
        tokensOutput.innerHTML = data.Tokens
        astOutput.innerHTML = data.Ast
        console.log("Response:", data);
    } 
    catch (err) {
        console.error("Error:", err);
    }
    finally {
        btn.disabled = false;
        btn.innerHTML = "<i class='fa-solid fa-play'></i> Submit Code";
    }
});