const fs = require('fs');
const cp = require('child_process');

// if we want to build for debug or release
var debug = false;

var exec = '';

var isLinux;

// if we want to cross compile to other platorms
var crossCompile = false;


process.argv.forEach(v => {
    if(v == '-debug') {
        debug = true;
    }

    if(v == '-cross-compile') {
        crossCompile = true;
    }

})

if(process.platform == 'linux') {
    exec = 'main'
    isLinux = true;
} else if(process.platform == 'win32' ) {
    exec = 'main.exe'
    isLinux = false;
}

// library arguments for linking
var libraries =  isLinux ? [''] : ['-lXinput'];

// library arguments for cross-compile

var crossCompileLibraies = ['-lcomctl32'];

// read the src directory for files

var readDir = isLinux ? './src/linux' : './src/windows';

fs.readdir(readDir, (err, f) => {
    if (err) {
        console.err("ERROR:", err);
        process.exit(0);
    } else {
        // exclude main because we are building object files
        // let files = f.filter(x => !x.includes('main'));

        f.forEach((v) => {
            let oName = v.replace('.c', '.o');
            try {
                fs.unlinkSync(`lib/${oName}`);
            } catch (error) {
                console.error(error);
            }
            // this is for -g flag which tells compiler to include debug symbols
            let g = debug ? '-g' : '';
            let lib = "";
            // fill lib variable with library arguments
            libraries.forEach((v) => lib = lib + " " + v);
            // ${g} ${v} -o ${oName} ${lib}
            let compilationString = "";
            if(crossCompile) {
                compilationString = `x86_64-w64-mingw32-gcc ${g} src/windows/${v} -o lib/${oName} ${lib} -c`;
            } else {
                compilationString =  isLinux ? `gcc ${g} src/linux/${v} -o lib/${oName} ${lib} -c` : `gcc ${g} src/windows/${v} -o lib/${oName} ${lib} -c`; 
            }
            console.log(compilationString);

            cp.execSync(compilationString, (err, stdout, stderr) => {
                if (err) {
                    console.error(err);
                    console.error(stderr);
                    process.exit(0);
                } else {
                    console.log(stdout);
                    console.log("Command Executed Successfully", oName);
                }
            });
        });

        let fileNames = "";
        let g = debug ? '-g' : '';
        f.forEach((v) => fileNames = fileNames + " " + "lib/" + v.replace('.c', '.o'));
        let lib = "";
        crossCompileLibraies.forEach((v) => lib = lib + " " + v);
        console.log(fileNames);
        if(crossCompile) {
            cp.exec(`x86_64-w64-mingw32-gcc ${g} src/main.c -o build/main.exe ${fileNames} ${crossCompileLibraies}`, (err, stdout, stderr) => {
                if (err) {
                    console.error(err);
                    console.error(stderr);
                    process.exit(0);
                } else {
                    console.log(stdout);
                    console.log(`Command Executed Successfully main.exe`);
                }
            })
        } else {
            cp.exec(`gcc ${g} src/main.c -o build/${exec} ${fileNames} ${lib}`, (err, stdout, stderr) => {
                if (err) {
                    console.error(err);
                    console.error(stderr);
                    process.exit(0);
                } else {
                    console.log(stdout);
                    console.log(`Command Executed Successfully ${exec}`);
                }
            })
        }  
    }
})
