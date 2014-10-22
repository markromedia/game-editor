#include "javascript_delegate.hpp"

#include "awesomium_handler.hpp"
#include "game.hpp"
#include "logger.hpp"
#include "es/system/transform_system.hpp"
#include "platform/FileSystem.hpp"

JavascriptDelegate::JavascriptDelegate(AwesomiumHandler* awesomium_handler, Awesomium::WebView* web_view) : _awesomium_handler(awesomium_handler), _web_view(web_view)
{
	Awesomium::JSValue delegate_value = _web_view->CreateGlobalJavascriptObject(Awesomium::WSLit("editor"));
	Awesomium::JSObject& delegate_js_obj = delegate_value.ToObject();

	//save remote id
	_delegate_remote_id = delegate_js_obj.remote_id();

	//register callbacks
	delegate_js_obj.SetCustomMethod(Awesomium::WSLit("init"), false);
	delegate_js_obj.SetCustomMethod(Awesomium::WSLit("listDirectory"), true);
	delegate_js_obj.SetCustomMethod(Awesomium::WSLit("loadFileContents"), true);
}

float f = .1f;
void JavascriptDelegate::OnMethodCall(Awesomium::WebView* caller, unsigned int remote_object_id, Awesomium::WebString const& method_name, Awesomium::JSArray const& args)
{
	if(remote_object_id == _delegate_remote_id
		&& method_name == Awesomium::WSLit("init"))
	{
		Awesomium::JSValue editor_value = _web_view->ExecuteJavascriptWithResult(Awesomium::WSLit("editor"), Awesomium::WSLit(""));
		Awesomium::JSObject& editor_obj = editor_value.ToObject();
		editor_obj.SetProperty(Awesomium::WSLit("absoluteDirectoryPath"), Awesomium::WSLit(FileSystem::GetExecutablePath().c_str()));
	}
}

Awesomium::JSValue JavascriptDelegate::OnMethodCallWithReturnValue(Awesomium::WebView* caller, unsigned remote_object_id, Awesomium::WebString const& method_name, Awesomium::JSArray const& args)
{

	if(remote_object_id == _delegate_remote_id &&
		 method_name == Awesomium::WSLit("listDirectory")
		 && args.size() > 0)
	{
		std::string directory = Awesomium::ToString(args[0].ToString());
		std::vector<File> files = FileSystem::ListDirectoryContents(directory);

		std::string json = std::string("[");
		for(std::vector<File>::iterator it = files.begin(); it != files.end(); ++it) {
			std::string icon = std::string("");
			if (it->_is_directory)
			{
				icon = std::string("res/folder_icon.png");
			}

			json.append("{\"name\" : \"").append(it->_file_name).append("\",")
				.append("\"icon\" : \"").append(icon).append("\",")
				.append("\"isDirectory\" : \"").append(it->_is_directory ? "true" : "false")
				.append("\"},");
		}
		json = json.substr(0, json.length() - 1);//remove extra ','
		json.append("]");
		return Awesomium::JSValue(Awesomium::WSLit(json.c_str()));
	} else 	if(remote_object_id == _delegate_remote_id &&
		 method_name == Awesomium::WSLit("loadFileContents")
		 && args.size() > 0)
	{
		std::string file = Awesomium::ToString(args[0].ToString());
		std::string fileContents("\""); 
		fileContents.append(reinterpret_cast<char*>(FileSystem::LoadFileContents(file, true))).append("\"");	
		return Awesomium::JSValue(Awesomium::WSLit(fileContents.c_str()));
	}

  return Awesomium::JSValue::Undefined();
}