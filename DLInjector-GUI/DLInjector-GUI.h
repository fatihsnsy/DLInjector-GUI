#include <iostream>
#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <comdef.h>
#include <vcclr.h>


namespace DLInjectorGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace std;



	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

		}

		HANDLE FindHandle(const wchar_t* procName) {

			PROCESSENTRY32 entry;
			entry.dwSize = sizeof(PROCESSENTRY32);

			HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

			if (snapshot == INVALID_HANDLE_VALUE) {
				infoBox->Text += "Snapshot failed! Error Code: " + GetLastError() + "\n";
				return NULL;
			}

			if (Process32First(snapshot, &entry) == TRUE) {
				while (Process32Next(snapshot, &entry) == TRUE) {

					if (_wcsicmp(entry.szExeFile, procName) == 0)
					{
						infoBox->Text += "Found the process! \n";

						HANDLE ProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

						if (ProcHandle == NULL)
						{
							infoBox->Text += "ProcHandle Failed! Error Code: " + GetLastError() + "\n";
							return NULL;
						}

						return ProcHandle;

					}
				}
			}

			return NULL;


		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: System::Windows::Forms::TextBox^ targetExe;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	public: System::Windows::Forms::TextBox^ injectedDll;


	private: System::Windows::Forms::Button^ doButton;
	public: System::Windows::Forms::RichTextBox^ infoBox;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ cancelBut;

	public:
	private:

	protected:

	private:

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->targetExe = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->injectedDll = (gcnew System::Windows::Forms::TextBox());
			this->doButton = (gcnew System::Windows::Forms::Button());
			this->infoBox = (gcnew System::Windows::Forms::RichTextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->cancelBut = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// targetExe
			// 
			this->targetExe->Location = System::Drawing::Point(195, 27);
			this->targetExe->Name = L"targetExe";
			this->targetExe->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->targetExe->Size = System::Drawing::Size(210, 20);
			this->targetExe->TabIndex = 0;
			this->targetExe->Text = L"Enter process name with .exe";
			this->targetExe->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->targetExe->GotFocus += gcnew System::EventHandler(this, &MyForm::targetExe_Enter);
			this->targetExe->LostFocus += gcnew System::EventHandler(this, &MyForm::targetExe_Leave);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(12, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 15);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Target Process Name ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(12, 67);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(124, 15);
			this->label2->TabIndex = 2;
			this->label2->Text = L"DLL to be Injected";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// injectedDll
			// 
			this->injectedDll->Location = System::Drawing::Point(194, 66);
			this->injectedDll->Name = L"injectedDll";
			this->injectedDll->Size = System::Drawing::Size(210, 20);
			this->injectedDll->TabIndex = 3;
			this->injectedDll->Text = L"Enter DLL path with .dll";
			this->injectedDll->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->injectedDll->GotFocus += gcnew System::EventHandler(this, &MyForm::injectedDll_Enter);
			this->injectedDll->LostFocus += gcnew System::EventHandler(this, &MyForm::injectedDll_Leave);
			// 
			// doButton
			// 
			this->doButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->doButton->Location = System::Drawing::Point(66, 103);
			this->doButton->Name = L"doButton";
			this->doButton->Size = System::Drawing::Size(113, 38);
			this->doButton->TabIndex = 5;
			this->doButton->Text = L"Let\'s Inject!";
			this->doButton->UseVisualStyleBackColor = true;
			this->doButton->Click += gcnew System::EventHandler(this, &MyForm::doButton_Click);
			// 
			// infoBox
			// 
			this->infoBox->BackColor = System::Drawing::Color::White;
			this->infoBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->infoBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->infoBox->Location = System::Drawing::Point(15, 163);
			this->infoBox->Name = L"infoBox";
			this->infoBox->ReadOnly = true;
			this->infoBox->Size = System::Drawing::Size(389, 150);
			this->infoBox->TabIndex = 6;
			this->infoBox->Text = L"--- DLInjector GUI InfoBox ---";
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::backgroundWorker1_DoWork);
			// 
			// cancelBut
			// 
			this->cancelBut->Enabled = false;
			this->cancelBut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->cancelBut->Location = System::Drawing::Point(249, 103);
			this->cancelBut->Name = L"cancelBut";
			this->cancelBut->Size = System::Drawing::Size(113, 38);
			this->cancelBut->TabIndex = 7;
			this->cancelBut->Text = L"Cancel";
			this->cancelBut->UseVisualStyleBackColor = true;
			this->cancelBut->Click += gcnew System::EventHandler(this, &MyForm::cancelBut_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->ClientSize = System::Drawing::Size(417, 325);
			this->Controls->Add(this->cancelBut);
			this->Controls->Add(this->infoBox);
			this->Controls->Add(this->doButton);
			this->Controls->Add(this->injectedDll);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->targetExe);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"DLInjector [GUI]";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

	}

		   // targetExe Textbox Placeholder
	private: System::Void targetExe_Enter(System::Object^ sender, System::EventArgs^ e) {

		if (targetExe->Text == "Enter process name with .exe") {
			targetExe->Text = "";
			targetExe->ForeColor = Color::Black;
		}

	}

	private: System::Void targetExe_Leave(System::Object^ sender, System::EventArgs^ e) {

		if (targetExe->Text == "") {
			targetExe->Text = "Enter process name with .exe";
			targetExe->ForeColor = Color::Gray;
		}

	}

		   //Injected DLL Textbox Placeholder
	private: System::Void injectedDll_Enter(System::Object^ sender, System::EventArgs^ e) {

		if (injectedDll->Text == "Enter DLL path with .dll") {
			injectedDll->Text = "";
			injectedDll->ForeColor = Color::Black;
		}

	}

	private: System::Void injectedDll_Leave(System::Object^ sender, System::EventArgs^ e) {

		if (injectedDll->Text == "") {
			injectedDll->Text = "Enter DLL path with .dll";
			injectedDll->ForeColor = Color::Gray;
		}

	}




	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void doButton_Click(System::Object^ sender, System::EventArgs^ e) {

		this->cancelBut->Enabled = true;
		backgroundWorker1->RunWorkerAsync(1);
	}


	private: System::Void cancelBut_Click(System::Object^ sender, System::EventArgs^ e) {


		backgroundWorker1->CancelAsync();
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

		backgroundWorker1->WorkerSupportsCancellation = true;
		HANDLE retHandle = NULL;
		PVOID buffer;
		PTHREAD_START_ROUTINE loadlibrary;


		pin_ptr<const wchar_t> dllstr = PtrToStringChars(injectedDll->Text);
		size_t convertedChars = 0;
		size_t sizeInBytes = ((injectedDll->Text->Length + 1) * 2);
		char* dllpath = (char*)malloc(sizeInBytes);
		wcstombs_s(&convertedChars, dllpath, sizeInBytes, dllstr, sizeInBytes);

		bool result;

		infoBox->Text = "Started the process\n";

		while (retHandle == NULL) {

			if (backgroundWorker1->CancellationPending) // Cancel isteði geldiðinde
			{
				e->Cancel = true;
				break;
			}

			pin_ptr<const wchar_t> wch = PtrToStringChars(targetExe->Text);
			retHandle = FindHandle(wch);
			if (retHandle == NULL) {
				infoBox->Text += "Waiting open the " + targetExe->Text + "\n";
				infoBox->ScrollToCaret();
				Thread::Sleep(1000);
			}

		}

		if (e->Cancel == true) {
			infoBox->Text += "Operation is cancelled!\n";
			this->cancelBut->Enabled = false;
			return;
		}

		infoBox->Text = "Allocating memory!" + "\n";

		buffer = VirtualAllocEx(retHandle, NULL, strlen(dllpath), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (buffer == NULL) {

			infoBox->Text += "Error allocte memory! Error Code: " + GetLastError() + "\n";
			return;
		}
		infoBox->Text += "Writing memory!\n";

		result = WriteProcessMemory(retHandle, buffer, dllpath, strlen(dllpath), NULL);
		if (!result) {
			infoBox->Text += "Error writing memory! Error Code: " + GetLastError() + "\n";
			return;
		}

		loadlibrary = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
		if (loadlibrary == NULL) {
			infoBox->Text += "Error GetProcAddress! Error Code: " + GetLastError() + "\n";
			return;
		}

		if ((CreateRemoteThread(retHandle, NULL, 0, loadlibrary, buffer, 0, NULL)) == NULL) {
			infoBox->Text += "Error CreateRemoteThread! Error Code: " + GetLastError() + "\n";
			return;
		}

		CloseHandle(retHandle);


		infoBox->Text += "All operations success! \n";
	}


};
}
