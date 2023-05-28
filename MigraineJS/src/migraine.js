export var migraineState = {
    version : "1.1",

    indexIncrement : 'e',
    passZeroFunction : '!',
    pipeFunction : '.',
    swapRegister : 'E',

    programCounter : 0,
    functionIndex : 0,
    integerStack : [],
    callStack : [],
    registers : [0, 0],
    currentRegister : 0,

    standardInput : "",
    standardOutput : "",
    callbackOutput : (output) => { return output; },

    functionList : []
}

function getRealFunctionIndex(migraineState) {
    return parseInt(migraineState.functionIndex / 2);
}

function setFunctionIndex(migraineState, register) {
    migraineState.functionIndex = parseInt(register);
    if (getRealFunctionIndex(migraineState) >= migraineState.functionList.length) {
        migraineState.functionIndex = 0;
    }
}

function getOppositeRegister(migraineState) {
    return migraineState.registers[migraineState.currentRegister === 0 ? 1 : 0];
}

function gotoIndex(migraineState, register) {
    setFunctionIndex(migraineState, register);
}
function number(migraineState, register) {
    return parseInt((register * 10) + getRealFunctionIndex(migraineState));
}
function add(migraineState, register) {
    return register + getOppositeRegister(migraineState);
}
function subtract(migraineState, register) {
    return register - getOppositeRegister(migraineState);
}
function multiply(migraineState, register) {
    return register * getOppositeRegister(migraineState);
}
function divide(migraineState, register) {
    return register / getOppositeRegister(migraineState);
}
function input(migraineState, register) {
    return migraineState.standardInput;
}
function outputInt(migraineState, register) {
    migraineState.standardOutput += parseInt(register).toString();
    migraineState.callbackOutput(migraineState.standardOutput);
    return register;
}
function outputChar(migraineState, register) {
    migraineState.standardOutput += String.fromCharCode(register);
    migraineState.callbackOutput(migraineState.standardOutput);
    return register;
}
function compareEquals(migraineState, register) {
    return register === getOppositeRegister(migraineState);
}
function compareGreater(migraineState, register) {
    return register > getOppositeRegister(migraineState);
}
function branch(migraineState, register) {
    let isBranching = register > 0;
    if (isBranching) {
        migraineState.callStack.push(migraineState.programCounter);
        migraineState.programCounter = getOppositeRegister(migraineState);
        migraineState.currentRegister = 0;
    }
    return register;
}
function branchReturn(migraineState, register) {
    let value = 0;
    if (migraineState.callStack.length > 0) {
        value = migraineState.callStack.pop();
    }
    migraineState.programCounter = register + value;
    return register;
}
function callStackPop(migraineState, register) {
    if (migraineState.callStack.length > 0) {
        migraineState.callStack.pop();
    }
    return register;
}
function stackPush(migraineState, register) {
    migraineState.integerStack.push(register);
    return register;
}
function stackPop(migraineState, register) {
    let value = 0;
    if (migraineState.integerStack.length > 0) {
        value = migraineState.integerStack.pop();
    }
    return value;
}
function stackRead(migraineState, register) {
    let value = 0;
    if (register < migraineState.integerStack.length) {
        value = migraineState.integerStack[register];
    }
    return value;
}
function stackWrite(migraineState, register) {
    if (register < migraineState.integerStack.length) {
        migraineState.integerStack[register] = getOppositeRegister(migraineState);
    }
    return register;
}

function initializeFunctionList(migraineState) {
    migraineState.functionList = [
        number, number, number, number, number, number, number, number, number, number,
        add,
        subtract,
        multiply,
        divide,
        input,
        outputInt,
        outputChar,
        compareEquals,
        compareGreater,
        branch,
        branchReturn,
        callStackPop,
        stackPush,
        stackPop,
        stackRead,
        stackWrite
    ];
}

function runFunction(migraineState, register) {
    let isGotoFunction = parseInt((migraineState.functionIndex + 1) % 2) === 0;
    if (isGotoFunction) {
        gotoIndex(migraineState, register);
    } else {
        migraineState.registers[migraineState.currentRegister] = migraineState.functionList.at(getRealFunctionIndex(migraineState))(migraineState, register);
    }
}

export function step(migraineState, program) {
    if (migraineState.programCounter >= program.length)
        return;

    let currentStep = program.charAt(migraineState.programCounter);

    if (currentStep === migraineState.indexIncrement) {
        setFunctionIndex(migraineState, migraineState.functionIndex + 1);
    }
    if (currentStep === migraineState.swapRegister) {
        migraineState.currentRegister = migraineState.currentRegister === 0 ? 1 : 0;
    }
    if (currentStep === migraineState.passZeroFunction) {
        runFunction(migraineState, 0);
    }
    if (currentStep === migraineState.pipeFunction) {
        runFunction(migraineState, migraineState.registers[migraineState.currentRegister]);
    }

    migraineState.programCounter += 1;
}

export function convertProgram (program) {
    return program.match(/([e!\.E]*)/g).join("");
}

export function run(migraineState, program) {
    let programLength = program.length;
    for (migraineState.programCounter = 0; migraineState.programCounter < programLength; migraineState.programCounter++) {
        let currentChar = program.charAt(migraineState.programCounter);
        step(migraineState, currentChar);
    }
}

export function initialize(migraineState) {
    initializeFunctionList(migraineState);
}

export function resetState(migraineState) {
    migraineState.programCounter = 0;
    migraineState.functionIndex = 0;
    migraineState.integerStack = [];
    migraineState.callStack = [];
    migraineState.registers = [0, 0];
    migraineState.currentRegister = 0;
    migraineState.functionList = [];

    migraineState.standardInput = "";
    migraineState.standardOutput = "";
}