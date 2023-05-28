import { migraineState, initialize, step, convertProgram, resetState } from "./migraine.js"

var debugProgram = document.getElementById("editor-debug");
var inputBox = document.getElementById("editor-input");
var loadProgramButton = document.getElementById("editor-load");
var stepProgramButton = document.getElementById("editor-step");
var runProgramButton = document.getElementById("editor-run");

function updateDebug(migraineState, debugProgram, programData) {
    let index = migraineState.programCounter;
    let spanTag = "<span style = 'color: white; background-color: blueviolet; font-size: 21px'>";

    debugProgram.innerHTML = programData.substring(0, index) + spanTag + programData.substring(index, index + 1) + "</span>" + programData.substring(index + 1);
}

var program = "";
loadProgramButton.addEventListener("click", () => {
    resetState(migraineState);
    initialize(migraineState);
    program = convertProgram(inputBox.value);
    updateDebug(migraineState, debugProgram, program);
});
stepProgramButton.addEventListener("click", () => {
    step(migraineState, program);
    updateDebug(migraineState, debugProgram, program);
});
runProgramButton.addEventListener("click", () => {
    resetState(migraineState);
    initialize(migraineState);

    for (let i = 0; i < program.length; i++) {
        step(migraineState, program);
    }

    console.log(migraineState.standardOutput);
});

