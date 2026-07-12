function changeWriteup(topicName, algorithm) {
    topicName = topicName.toLowerCase();
    algorithm = algorithm.toLowerCase().split(" ").join("-");
    window.location.href = "/write-ups/" + topicName + "/" + algorithm
    console.log(topicName, algorithm)
}