package com.talktic;

import org.mozilla.javascript.*;

import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Vector;

public class JavaScriptCompiler {
	protected Context context;

	protected Scriptable global;

	protected boolean isSystemLibraryLoaded;

	public JavaScriptCompiler(boolean loadSystemLibrary) throws IOException {
		context = Context.enter();
		global = context.initStandardObjects();
		try {
			ScriptableObject.defineClass(global, com.talktic.JSFile.class);
			ScriptableObject.putProperty(global, "stdout", Context.javaToJS(System.out, global));
			ScriptableObject.putProperty(global, "stderr", Context.javaToJS(System.err, global));
			if (loadSystemLibrary) {
				InputStream is = ClassLoader.getSystemResourceAsStream("jsc.js");
				if (is != null) {
					context.evaluateReader(global, new InputStreamReader(is), "<base>", 1, null);
					isSystemLibraryLoaded = true;
				}
			}
		} catch (Exception e) {
			System.err.println(e);
		}
	}

	public void loadScript(File script) throws IOException {
		try {
			context.evaluateReader(global, new FileReader(script), script.getPath(), 1, null);
		} catch (FileNotFoundException e) {
			System.err.println(e);
		}
	}

	public void load(String path) throws IOException {
		File files = new File(path);
		if (files.isDirectory()) {
			for (File f : files.listFiles(new FileFilter() {
				public boolean accept(File f) {
					return f.getName().endsWith(".js");
				}
			})) {
				loadScript(f);
			}
		} else {
			loadScript(files);
		}
	}

	public void compile(String src, String asm, String bc) {
		if (asm == null) {
			asm = src + ".asm";
		}
		if (bc == null) {
			bc = src + ".bc";
		}
		Object result = context.evaluateString(global, "JSC$compile_file('" + src
				+ "',JSC$FLAG_VERBOSE,'" + asm + "','" + bc + "');", "<str>", 1, null);
		//System.out.println(Context.toString(result));
	}

	public static void main(String[] args) {
		boolean loadSystemLibrary = true;
		String asmPath = null, bytecodePath = null, sourcePath = null;
		Vector<String> baseLibraryPathList = new Vector<String>();

		for (String arg : args) {
			if (arg.startsWith("-L")) {
				baseLibraryPathList.addElement(arg.substring(3));
			} else if (arg.startsWith("-A")) {
				asmPath = arg.substring(3);
			} else if (arg.startsWith("-B")) {
				bytecodePath = arg.substring(3);
			} else if (arg == "-n") {
				loadSystemLibrary = false;
			} else {
				sourcePath = arg;
			}
		}

		if (sourcePath == null) {
			System.out.println("java -jar jsc.jar [-n] [-Lpath] [-Afile] [-Bfile] source");
			System.out.println("\t-n              don't load system library");
			System.out.println("\t-Llibrary_path  additional library dir/file path");
			System.out.println("\t-Lasm_file      asm output file path");
			System.out.println("\t-Lbc_file       bytecode ouput file path");
			return;
		}

		try {
			JavaScriptCompiler jsc = new JavaScriptCompiler(loadSystemLibrary);
			for(int i=0; i<baseLibraryPathList.size(); i++) {
				jsc.load(baseLibraryPathList.get(i));
			}
			jsc.compile(sourcePath, asmPath, bytecodePath);
		} catch (Exception e) {
			System.err.println(e);
		}
	}
}
