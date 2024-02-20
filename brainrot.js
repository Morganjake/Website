var VideoGrid = document.getElementById("VideoGrid");
var VideoUrls = [
    "ChBg4aowzX8",
    "Q4MOP8s9KyY",
    "pt_k_HNz1DE",
    "fuQf-iGCmKA",
    "qXcMNBQnQMM",
    "PVOCPGXYA0w",
    "-FR1lXLEcmM",
    "LjtVRw9af2U",
    "10gjsgA6fTE",
    "a_r3QouhG3E",
    "1Dxqmd4lA7Y",
    "rs9BZg4gDW0",
    "vD-NlntuD6Y",
    "n_Dv4JMiwK8",
    "jTYH3eCGHTM",
    "PERqJhJG12I",
    "5mGuCdlCcNM",
    "gBAKe472zus",
    "RojwXNJZYHg",
    "VoVJECL-2NA",
    "fu2gdoP8AFk", // Background
    "7Ge7Ajbzc0U"  //
]
var player;

function onYouTubeIframeAPIReady() {

    VideoCount = 1

    VideoUrls.forEach(function (VideoUrl) {
        var VideoDiv = document.createElement("div");
        var IsBackgroundVideo = VideoUrl == "fu2gdoP8AFk" || VideoUrl == "7Ge7Ajbzc0U";

        if (IsBackgroundVideo) { // Seperate code for the background videos
            Body = document.getElementById("Body");
            VideoDiv.id = `Video ${VideoCount}`;
            VideoDiv.className = `Background`
            VideoDiv.style.opacity = VideoUrl == "fu2gdoP8AFk" ? 0.03 : 0.3; // Sets opacity
            Body.appendChild(VideoDiv);
        }
        else {
            VideoDiv.id = `Video ${VideoCount}`
            VideoDiv.className = `Brainrot`
            VideoGrid.appendChild(VideoDiv);
        }

        player = new YT.Player(`Video ${VideoCount}`, {
            videoId: VideoUrl,
            playerVars: { // Stops you from interacting with all the youtube stuff
                autoplay: 1,
                controls: 0, 
                modestbranding: 1,
                showinfo: 0,
                fs: 0,
                rel: 0,
                mute: 1 
            }
        });
        VideoCount++;
    });
}


// Event runs when you click off the tab
window.addEventListener("blur", () =>{
    document.title = "YOU MUST ROT"
})


// Event runs when you click on the tab
window.addEventListener("focus", () =>{
    document.title = "YOU ARE ENLIGHTENED"
})