
var Selected = [];
var Haunted = [];

function GenerateButtons() {
    var Grid = document.getElementById('ButtonGrid');

    for (Row = 0; Row < 5; Row++) {
        for (Column = 0; Column < 5; Column++) {
            
            var ButtonGrid = document.getElementById("ButtonGrid");
            var Button = document.createElement("div");
            Button.className = "Button";
            
            if (Math.random() < 0.5) {
                Button.id = "Haunted"
                Haunted.push(Button)
            }
            else {
                Button.id = "Not Haunted"
            }

            ButtonGrid.appendChild(Button);
        }
    }
}

document.body.addEventListener("click", function(event) {
    if (event.target.classList.contains("Button")) {
        
        if (Selected.includes(event.target)) {
            event.target.style.borderColor = `white`
            Selected.splice(Selected.indexOf(event.target), 1)
        }
        else {
            event.target.style.borderColor = `blue`
            Selected.push(event.target)
        }
        console.log(Selected)
    }
});

function VerifyCaptcha() {

    console.log("fghfgh")
    if (Selected.length == Haunted.length) {
        console.log("fghfgh")
        Passed = true
        Selected.forEach(Button => {
            if (!Haunted.includes(Button)) {
                Passed = false;
            } 
        });
    }
    else {
        Passed = false
    }

    if (!Passed) {
        var ErrorMessage = document.getElementById("ErrorMessage");
        ErrorMessage.textContent = "Please check the box to confirm that you are not a robot.";
        ErrorMessage.style.color = "red";
    }
    else {
        window.location.href = "3.html";
    }
}
