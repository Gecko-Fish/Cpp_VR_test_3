// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UMyBlueprintFunctionLibrary::HttpReq(const FString& Url, const FString& HttpMethod = "GET", const FString& Payload = "")
{
    // Get the HTTP module
    FHttpModule& HttpModule = FHttpModule::Get();

    // Create a request
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = HttpModule.CreateRequest();
    
    if (!Payload.IsEmpty()) {
        Request->SetContentAsString(Payload);
    }

    // Set the HTTP method
    Request->SetVerb(HttpMethod);
    
    // Set the URL for the API call
    Request->SetURL(Url);

    // Set up the response processing
    Request->OnProcessRequestComplete().BindLambda(
        [&](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
            if (bSuccess && HttpResponse.IsValid()) {
                // Handle the response data here
                FString Response = HttpResponse->GetContentAsString();
                // Process the 'Response' data
                UE_LOG(LogTemp, Log, TEXT("Http request made:"));
                UE_LOG(LogTemp, Log, TEXT("%s"), *Response);
            } else {
                // Log an error if the request fails
                UE_LOG(LogTemp, Error, TEXT("Request failed."));
            }
        }
    );

    // Send the request
    Request->ProcessRequest();
}


// void YourClass::YourFunction()
// {
//         TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

//         JsonObject->SetStringField(TEXT("some_string_field"), *FString::Printf(TEXT("%s"), *SomeFStringVariable));

//         FString OutputString;

//         TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

//         FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

//         TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

//         HttpRequest->SetVerb("POST");

//         HttpRequest->SetHeader("Content-Type", "application/json");

//         HttpRequest->SetURL(*FString::Printf(TEXT("%s"), *UrlAddressAsString));

//         HttpRequest->SetContentAsString(OutputString);

//         HttpRequest->OnProcessRequestComplete().BindUObject(this, &YourClass::OnYourFunctionCompleted);

//         HttpRequest->ProcessRequest();
// }

// void YourClass::OnYourFunctionCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
// {
//     if (bWasSuccessful && Response->GetContentType() == "application/json")
//     {
//         TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

//         TSharedRef<TJsonReader<TCHAR>> JsonReader =  TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

//         FJsonSerializer::Deserialize(JsonReader, JsonObject);

//         SomeOtherVariable = JsonObject->GetStringField("some_response_field");

//     }
//     else
//     {
//         // Handle error here
//     }
// }