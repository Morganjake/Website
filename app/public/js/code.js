
function changeTab(newTab) {
	Array.from(document.getElementsByClassName("tab")).forEach(tab => {
		tab.id = tab.innerHTML == newTab ? "selected" : "";
	});

	Array.from(document.getElementsByClassName("output")).forEach(tab => {
		tab.hidden = tab.id != newTab.toLowerCase() + "-output";
	});
}

const editor = document.getElementById('code-input');
const btn = document.getElementById('submit-button');

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
		console.log("Response:", data);
	} catch (err) {
		console.error("Error:", err);
	} finally {
		btn.disabled = false;
		btn.textContent = "Submit Code";
	}
});