#pragma once

#include "main_hmm.h"

int gui_lang_index = lang_index_begin;
int gui_song_index = 0;
time_t gui_timestamp ;

namespace SPPlayList {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WndMainPlayList
	/// </summary>
	public ref class WndMainPlayList : public System::Windows::Forms::Form
	{
	public:
		WndMainPlayList(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WndMainPlayList()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  picture_boy;
	protected: 

	protected: 
	private: System::Windows::Forms::Label^  Label_Lang_Hindi;
	private: System::Windows::Forms::Label^  Label_Lang_English;
	private: System::Windows::Forms::Button^  liveTrain_hindi;
	private: System::Windows::Forms::Button^  liveTrain_English;
	private: System::Windows::Forms::Button^  Test_Lang;
	private: System::Windows::Forms::Label^  lang_result;
	private: System::Windows::Forms::Button^  console_app_button;
	private: System::Windows::Forms::Label^  LABEL_SONG1;
	private: System::Windows::Forms::Label^  LABEL_SONG2;
	private: System::Windows::Forms::Label^  LABEL_SONG3;
	private: System::Windows::Forms::Label^  LABEL_SONG4;




	private: System::Windows::Forms::Label^  LABEL_SONG0;








	private: System::Windows::Forms::Button^  live_train_index0;
	private: System::Windows::Forms::Button^  live_train_index1;
	private: System::Windows::Forms::Button^  live_train_index2;
	private: System::Windows::Forms::Button^  live_train_index3;
	private: System::Windows::Forms::Button^  live_train_index4;







	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button_reset;
	private: System::Windows::Forms::Label^  label_playing_now;
	private: System::Windows::Forms::Button^  button_speak_index;
	private: System::Windows::Forms::ListView^  lang_listview;
	private: System::Windows::Forms::ColumnHeader^  LIST_LANG_NAME;
	private: System::Windows::Forms::ColumnHeader^  LIST_LANG_Lindex;
	private: System::Windows::Forms::Button^  LiveTrain_Lang_new;












	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WndMainPlayList::typeid));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"item1"));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"item2222222222222222"));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L"item3"));
			System::Windows::Forms::ListViewItem^  listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L"item4"));
			System::Windows::Forms::ListViewItem^  listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(L"item5"));
			this->picture_boy = (gcnew System::Windows::Forms::PictureBox());
			this->Label_Lang_Hindi = (gcnew System::Windows::Forms::Label());
			this->Label_Lang_English = (gcnew System::Windows::Forms::Label());
			this->liveTrain_hindi = (gcnew System::Windows::Forms::Button());
			this->liveTrain_English = (gcnew System::Windows::Forms::Button());
			this->Test_Lang = (gcnew System::Windows::Forms::Button());
			this->lang_result = (gcnew System::Windows::Forms::Label());
			this->console_app_button = (gcnew System::Windows::Forms::Button());
			this->LABEL_SONG1 = (gcnew System::Windows::Forms::Label());
			this->LABEL_SONG2 = (gcnew System::Windows::Forms::Label());
			this->LABEL_SONG3 = (gcnew System::Windows::Forms::Label());
			this->LABEL_SONG4 = (gcnew System::Windows::Forms::Label());
			this->LABEL_SONG0 = (gcnew System::Windows::Forms::Label());
			this->live_train_index0 = (gcnew System::Windows::Forms::Button());
			this->live_train_index1 = (gcnew System::Windows::Forms::Button());
			this->live_train_index2 = (gcnew System::Windows::Forms::Button());
			this->live_train_index3 = (gcnew System::Windows::Forms::Button());
			this->live_train_index4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_reset = (gcnew System::Windows::Forms::Button());
			this->label_playing_now = (gcnew System::Windows::Forms::Label());
			this->button_speak_index = (gcnew System::Windows::Forms::Button());
			this->lang_listview = (gcnew System::Windows::Forms::ListView());
			this->LIST_LANG_NAME = (gcnew System::Windows::Forms::ColumnHeader());
			this->LIST_LANG_Lindex = (gcnew System::Windows::Forms::ColumnHeader());
			this->LiveTrain_Lang_new = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_boy))->BeginInit();
			this->SuspendLayout();
			// 
			// picture_boy
			// 
			this->picture_boy->BackColor = System::Drawing::Color::Transparent;
			this->picture_boy->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"picture_boy.BackgroundImage")));
			this->picture_boy->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->picture_boy->Location = System::Drawing::Point(237, 1);
			this->picture_boy->Name = L"picture_boy";
			this->picture_boy->Size = System::Drawing::Size(150, 245);
			this->picture_boy->TabIndex = 0;
			this->picture_boy->TabStop = false;
			// 
			// Label_Lang_Hindi
			// 
			this->Label_Lang_Hindi->AutoSize = true;
			this->Label_Lang_Hindi->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->Label_Lang_Hindi->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_Lang_Hindi->ForeColor = System::Drawing::Color::DarkOrchid;
			this->Label_Lang_Hindi->Location = System::Drawing::Point(72, 43);
			this->Label_Lang_Hindi->Name = L"Label_Lang_Hindi";
			this->Label_Lang_Hindi->Size = System::Drawing::Size(118, 43);
			this->Label_Lang_Hindi->TabIndex = 1;
			this->Label_Lang_Hindi->Text = L"HINDI";
			this->Label_Lang_Hindi->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Label_Lang_English
			// 
			this->Label_Lang_English->AutoSize = true;
			this->Label_Lang_English->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->Label_Lang_English->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Label_Lang_English->ForeColor = System::Drawing::Color::DarkViolet;
			this->Label_Lang_English->Location = System::Drawing::Point(72, 102);
			this->Label_Lang_English->Name = L"Label_Lang_English";
			this->Label_Lang_English->Size = System::Drawing::Size(159, 43);
			this->Label_Lang_English->TabIndex = 2;
			this->Label_Lang_English->Text = L"ENGLISH";
			// 
			// liveTrain_hindi
			// 
			this->liveTrain_hindi->BackColor = System::Drawing::Color::Transparent;
			this->liveTrain_hindi->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 9, System::Drawing::FontStyle::Bold));
			this->liveTrain_hindi->ForeColor = System::Drawing::Color::Gray;
			this->liveTrain_hindi->Location = System::Drawing::Point(8, 40);
			this->liveTrain_hindi->Name = L"liveTrain_hindi";
			this->liveTrain_hindi->Size = System::Drawing::Size(55, 50);
			this->liveTrain_hindi->TabIndex = 3;
			this->liveTrain_hindi->Text = L"Live Train";
			this->liveTrain_hindi->UseVisualStyleBackColor = false;
			this->liveTrain_hindi->Click += gcnew System::EventHandler(this, &WndMainPlayList::liveTrain_hindi_Click);
			// 
			// liveTrain_English
			// 
			this->liveTrain_English->BackColor = System::Drawing::Color::Transparent;
			this->liveTrain_English->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 9, System::Drawing::FontStyle::Bold));
			this->liveTrain_English->ForeColor = System::Drawing::Color::Gray;
			this->liveTrain_English->Location = System::Drawing::Point(7, 99);
			this->liveTrain_English->Name = L"liveTrain_English";
			this->liveTrain_English->Size = System::Drawing::Size(55, 50);
			this->liveTrain_English->TabIndex = 4;
			this->liveTrain_English->Text = L"Live Train";
			this->liveTrain_English->UseVisualStyleBackColor = false;
			this->liveTrain_English->Click += gcnew System::EventHandler(this, &WndMainPlayList::liveTrain_English_Click);
			// 
			// Test_Lang
			// 
			this->Test_Lang->BackColor = System::Drawing::Color::MediumAquamarine;
			this->Test_Lang->Font = (gcnew System::Drawing::Font(L"Source Sans Pro", 12, System::Drawing::FontStyle::Bold));
			this->Test_Lang->ForeColor = System::Drawing::Color::DarkMagenta;
			this->Test_Lang->Location = System::Drawing::Point(7, 247);
			this->Test_Lang->Name = L"Test_Lang";
			this->Test_Lang->Size = System::Drawing::Size(216, 42);
			this->Test_Lang->TabIndex = 5;
			this->Test_Lang->Text = L"SPEAK LANGAUGE";
			this->Test_Lang->UseVisualStyleBackColor = false;
			this->Test_Lang->Click += gcnew System::EventHandler(this, &WndMainPlayList::speak_lang_Click_1);
			// 
			// lang_result
			// 
			this->lang_result->AutoSize = true;
			this->lang_result->BackColor = System::Drawing::Color::SeaShell;
			this->lang_result->Font = (gcnew System::Drawing::Font(L"Quicksand", 12, System::Drawing::FontStyle::Bold));
			this->lang_result->ForeColor = System::Drawing::Color::OrangeRed;
			this->lang_result->Location = System::Drawing::Point(518, 12);
			this->lang_result->Name = L"lang_result";
			this->lang_result->Size = System::Drawing::Size(18, 23);
			this->lang_result->TabIndex = 6;
			this->lang_result->Text = L"-";
			// 
			// console_app_button
			// 
			this->console_app_button->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->console_app_button->Font = (gcnew System::Drawing::Font(L"Source Sans Pro", 12, System::Drawing::FontStyle::Bold));
			this->console_app_button->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->console_app_button->Location = System::Drawing::Point(235, 253);
			this->console_app_button->Name = L"console_app_button";
			this->console_app_button->Size = System::Drawing::Size(152, 35);
			this->console_app_button->TabIndex = 7;
			this->console_app_button->Text = L"CONSOLE APP";
			this->console_app_button->UseVisualStyleBackColor = false;
			this->console_app_button->Click += gcnew System::EventHandler(this, &WndMainPlayList::console_app_Click);
			// 
			// LABEL_SONG1
			// 
			this->LABEL_SONG1->AutoSize = true;
			this->LABEL_SONG1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LABEL_SONG1->Font = (gcnew System::Drawing::Font(L"Raleway", 12, System::Drawing::FontStyle::Italic));
			this->LABEL_SONG1->Location = System::Drawing::Point(432, 95);
			this->LABEL_SONG1->Name = L"LABEL_SONG1";
			this->LABEL_SONG1->Size = System::Drawing::Size(73, 24);
			this->LABEL_SONG1->TabIndex = 9;
			this->LABEL_SONG1->Text = L"SONG1";
			// 
			// LABEL_SONG2
			// 
			this->LABEL_SONG2->AutoSize = true;
			this->LABEL_SONG2->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LABEL_SONG2->Font = (gcnew System::Drawing::Font(L"Raleway", 12, System::Drawing::FontStyle::Italic));
			this->LABEL_SONG2->Location = System::Drawing::Point(432, 134);
			this->LABEL_SONG2->Name = L"LABEL_SONG2";
			this->LABEL_SONG2->Size = System::Drawing::Size(75, 24);
			this->LABEL_SONG2->TabIndex = 10;
			this->LABEL_SONG2->Text = L"SONG2";
			// 
			// LABEL_SONG3
			// 
			this->LABEL_SONG3->AutoSize = true;
			this->LABEL_SONG3->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LABEL_SONG3->Font = (gcnew System::Drawing::Font(L"Raleway", 12, System::Drawing::FontStyle::Italic));
			this->LABEL_SONG3->Location = System::Drawing::Point(432, 173);
			this->LABEL_SONG3->Name = L"LABEL_SONG3";
			this->LABEL_SONG3->Size = System::Drawing::Size(75, 24);
			this->LABEL_SONG3->TabIndex = 11;
			this->LABEL_SONG3->Text = L"SONG3";
			// 
			// LABEL_SONG4
			// 
			this->LABEL_SONG4->AutoSize = true;
			this->LABEL_SONG4->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LABEL_SONG4->Font = (gcnew System::Drawing::Font(L"Raleway", 12, System::Drawing::FontStyle::Italic));
			this->LABEL_SONG4->Location = System::Drawing::Point(432, 214);
			this->LABEL_SONG4->Name = L"LABEL_SONG4";
			this->LABEL_SONG4->Size = System::Drawing::Size(76, 24);
			this->LABEL_SONG4->TabIndex = 12;
			this->LABEL_SONG4->Text = L"SONG4";
			// 
			// LABEL_SONG0
			// 
			this->LABEL_SONG0->AutoSize = true;
			this->LABEL_SONG0->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LABEL_SONG0->Font = (gcnew System::Drawing::Font(L"Raleway", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LABEL_SONG0->Location = System::Drawing::Point(432, 54);
			this->LABEL_SONG0->Name = L"LABEL_SONG0";
			this->LABEL_SONG0->Size = System::Drawing::Size(77, 24);
			this->LABEL_SONG0->TabIndex = 8;
			this->LABEL_SONG0->Text = L"SONG0";
			// 
			// live_train_index0
			// 
			this->live_train_index0->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->live_train_index0->Location = System::Drawing::Point(391, 52);
			this->live_train_index0->Name = L"live_train_index0";
			this->live_train_index0->Size = System::Drawing::Size(28, 28);
			this->live_train_index0->TabIndex = 13;
			this->live_train_index0->Text = L"LT";
			this->live_train_index0->UseVisualStyleBackColor = true;
			this->live_train_index0->Click += gcnew System::EventHandler(this, &WndMainPlayList::live_train_index0_Click);
			// 
			// live_train_index1
			// 
			this->live_train_index1->AllowDrop = true;
			this->live_train_index1->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->live_train_index1->Location = System::Drawing::Point(391, 92);
			this->live_train_index1->Name = L"live_train_index1";
			this->live_train_index1->Size = System::Drawing::Size(28, 28);
			this->live_train_index1->TabIndex = 14;
			this->live_train_index1->Text = L"LT";
			this->live_train_index1->UseVisualStyleBackColor = true;
			this->live_train_index1->Click += gcnew System::EventHandler(this, &WndMainPlayList::live_train_index1_Click);
			// 
			// live_train_index2
			// 
			this->live_train_index2->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->live_train_index2->Location = System::Drawing::Point(391, 131);
			this->live_train_index2->Name = L"live_train_index2";
			this->live_train_index2->Size = System::Drawing::Size(28, 28);
			this->live_train_index2->TabIndex = 15;
			this->live_train_index2->Text = L"LT";
			this->live_train_index2->UseVisualStyleBackColor = true;
			this->live_train_index2->Click += gcnew System::EventHandler(this, &WndMainPlayList::live_train_index2_Click);
			// 
			// live_train_index3
			// 
			this->live_train_index3->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->live_train_index3->Location = System::Drawing::Point(391, 171);
			this->live_train_index3->Name = L"live_train_index3";
			this->live_train_index3->Size = System::Drawing::Size(28, 28);
			this->live_train_index3->TabIndex = 16;
			this->live_train_index3->Text = L"LT";
			this->live_train_index3->UseVisualStyleBackColor = true;
			this->live_train_index3->Click += gcnew System::EventHandler(this, &WndMainPlayList::live_train_index3_Click);
			// 
			// live_train_index4
			// 
			this->live_train_index4->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->live_train_index4->Location = System::Drawing::Point(390, 213);
			this->live_train_index4->Name = L"live_train_index4";
			this->live_train_index4->Size = System::Drawing::Size(28, 28);
			this->live_train_index4->TabIndex = 17;
			this->live_train_index4->Text = L"LT";
			this->live_train_index4->UseVisualStyleBackColor = true;
			this->live_train_index4->Click += gcnew System::EventHandler(this, &WndMainPlayList::live_train_index4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->label1->Font = (gcnew System::Drawing::Font(L"Quicksand", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(432, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 23);
			this->label1->TabIndex = 19;
			this->label1->Text = L"SONGS";
			// 
			// button_reset
			// 
			this->button_reset->BackColor = System::Drawing::Color::Chocolate;
			this->button_reset->Font = (gcnew System::Drawing::Font(L"Source Sans Pro", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_reset->ForeColor = System::Drawing::Color::Gold;
			this->button_reset->Location = System::Drawing::Point(723, 253);
			this->button_reset->Name = L"button_reset";
			this->button_reset->Size = System::Drawing::Size(167, 36);
			this->button_reset->TabIndex = 20;
			this->button_reset->Text = L"RESET PLAYLIST";
			this->button_reset->UseVisualStyleBackColor = false;
			this->button_reset->Click += gcnew System::EventHandler(this, &WndMainPlayList::button_reset_Click);
			// 
			// label_playing_now
			// 
			this->label_playing_now->AutoSize = true;
			this->label_playing_now->BackColor = System::Drawing::Color::SeaShell;
			this->label_playing_now->Font = (gcnew System::Drawing::Font(L"Lucida Handwriting", 10, System::Drawing::FontStyle::Bold));
			this->label_playing_now->ForeColor = System::Drawing::Color::Crimson;
			this->label_playing_now->Location = System::Drawing::Point(237, 297);
			this->label_playing_now->Name = L"label_playing_now";
			this->label_playing_now->Size = System::Drawing::Size(467, 23);
			this->label_playing_now->TabIndex = 21;
			this->label_playing_now->Text = L"Playing Right Now: Tera Chera Nazar Aaye";
			// 
			// button_speak_index
			// 
			this->button_speak_index->BackColor = System::Drawing::Color::MediumAquamarine;
			this->button_speak_index->Font = (gcnew System::Drawing::Font(L"Source Sans Pro", 12, System::Drawing::FontStyle::Bold));
			this->button_speak_index->ForeColor = System::Drawing::Color::DarkMagenta;
			this->button_speak_index->Location = System::Drawing::Point(437, 253);
			this->button_speak_index->Name = L"button_speak_index";
			this->button_speak_index->Size = System::Drawing::Size(232, 35);
			this->button_speak_index->TabIndex = 18;
			this->button_speak_index->Text = L"SPEAK INDEX (0-4)";
			this->button_speak_index->UseVisualStyleBackColor = false;
			this->button_speak_index->Click += gcnew System::EventHandler(this, &WndMainPlayList::button_speak_index_Click);
			// 
			// lang_listview
			// 
			this->lang_listview->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->lang_listview->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->LIST_LANG_NAME, 
				this->LIST_LANG_Lindex});
			this->lang_listview->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 15, System::Drawing::FontStyle::Bold));
			this->lang_listview->ForeColor = System::Drawing::Color::DarkViolet;
			this->lang_listview->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(5) {listViewItem1, listViewItem2, 
				listViewItem3, listViewItem4, listViewItem5});
			this->lang_listview->Location = System::Drawing::Point(7, 12);
			this->lang_listview->MultiSelect = false;
			this->lang_listview->Name = L"lang_listview";
			this->lang_listview->Size = System::Drawing::Size(224, 229);
			this->lang_listview->TabIndex = 22;
			this->lang_listview->UseCompatibleStateImageBehavior = false;
			this->lang_listview->View = System::Windows::Forms::View::Details;
			this->lang_listview->SelectedIndexChanged += gcnew System::EventHandler(this, &WndMainPlayList::lang_listview_SelectedIndexChanged);
			// 
			// LIST_LANG_NAME
			// 
			this->LIST_LANG_NAME->Text = L"LANG NAME";
			this->LIST_LANG_NAME->Width = 184;
			// 
			// LIST_LANG_Lindex
			// 
			this->LIST_LANG_Lindex->Text = L"Wi";
			// 
			// LiveTrain_Lang_new
			// 
			this->LiveTrain_Lang_new->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 7));
			this->LiveTrain_Lang_new->Location = System::Drawing::Point(12, 295);
			this->LiveTrain_Lang_new->Name = L"LiveTrain_Lang_new";
			this->LiveTrain_Lang_new->Size = System::Drawing::Size(211, 26);
			this->LiveTrain_Lang_new->TabIndex = 23;
			this->LiveTrain_Lang_new->Text = L"LIVE TRAIN Langauge";
			this->LiveTrain_Lang_new->UseVisualStyleBackColor = true;
			this->LiveTrain_Lang_new->Click += gcnew System::EventHandler(this, &WndMainPlayList::LiveTrain_Lang_new_Click);
			// 
			// WndMainPlayList
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 26);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(934, 325);
			this->Controls->Add(this->LiveTrain_Lang_new);
			this->Controls->Add(this->lang_listview);
			this->Controls->Add(this->label_playing_now);
			this->Controls->Add(this->button_reset);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_speak_index);
			this->Controls->Add(this->live_train_index4);
			this->Controls->Add(this->live_train_index3);
			this->Controls->Add(this->live_train_index2);
			this->Controls->Add(this->live_train_index1);
			this->Controls->Add(this->live_train_index0);
			this->Controls->Add(this->LABEL_SONG4);
			this->Controls->Add(this->LABEL_SONG3);
			this->Controls->Add(this->LABEL_SONG2);
			this->Controls->Add(this->LABEL_SONG1);
			this->Controls->Add(this->LABEL_SONG0);
			this->Controls->Add(this->console_app_button);
			this->Controls->Add(this->lang_result);
			this->Controls->Add(this->Test_Lang);
			this->Controls->Add(this->liveTrain_English);
			this->Controls->Add(this->liveTrain_hindi);
			this->Controls->Add(this->Label_Lang_English);
			this->Controls->Add(this->Label_Lang_Hindi);
			this->Controls->Add(this->picture_boy);
			this->DoubleBuffered = true;
			this->Font = (gcnew System::Drawing::Font(L"Tempus Sans ITC", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"WndMainPlayList";
			this->Text = L"SONG PLAYLIST";
			this->Load += gcnew System::EventHandler(this, &WndMainPlayList::WndMainPlayList_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->picture_boy))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
// when forms Loads
	private: System::Void WndMainPlayList_Load(System::Object^  sender, System::EventArgs^  e) {
		CalculateWeightsForRaisedSineWindow();	// calculating weights for Raised sine window before hand using in program.
		read_codebook_from_file();				// read codebook from file.
		read_words();

		this->Test_Lang->Enabled = true;

		this->button_speak_index->Enabled = false;
		this->button_speak_index->BackColor = System::Drawing::Color::LightGray;
		this->button_speak_index->ForeColor = System::Drawing::Color::Gray;
			
		this->LABEL_SONG0->Text = L"0. ";
		this->LABEL_SONG1->Text = L"1. ";
		this->LABEL_SONG2->Text = L"2. ";
		this->LABEL_SONG3->Text = L"3. ";
		this->LABEL_SONG4->Text = L"4. ";

		this->label_playing_now->Text = L"";

		this->LiveTrain_Lang_new->Visible=false;

		lang_listview->Items->Clear();
		for(int lg=lang_index_begin; lg<totWords;lg++)
		{
		  ListViewItem^ item1 = gcnew ListViewItem( gcnew String(strupr(HMM_WORDS[lg])),0 );
		  item1->SubItems->Add( lg.ToString() );
		  lang_listview->Items->Add( item1 );
		}

	}// when forms Loads
	
//SPEAK LANG CODE
	private: System::Void speak_lang_Click_1(System::Object^  sender, System::EventArgs^  e) {
		read_playlist_songs();
		//BUTTONS
		this->Test_Lang->Enabled = false;	//disable this button
		this->Test_Lang->BackColor = System::Drawing::Color::LightGray;
		this->Test_Lang->ForeColor = System::Drawing::Color::Gray;
			

		char model_type_string[20] = "new_model";
		unsigned int model_type_use = OutputFolderModel;

		printf("\n <-------->");
		printf("\n Duration 3 sec: RECORDING LANG: \n");

		gui_timestamp = time(NULL);

		/**************** Creating necessary file Path for data. ****************/
		sprintf(liveRecordingFileName, "gui_playlist_livetest_%ld_lang", gui_timestamp);  //file_name
		sprintf(liveRecordingCommand, "%s 3 %s %s%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
		//printf("\n path: %s\n",liveRecordingCommand );
		/**************** Creating necessary file Path for data. ****************/
			sprintf(completePathOuput, "%s%s_testresult_%s.txt", input_live_voice_folder, liveRecordingFileName ,model_type_string);  
			/**************** Opening respective files. ****************/
			fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
			if(fp_console == NULL){ 
					perror("\n Error: ");
					this->lang_result->Text = "Error: Console Output File";
					printf("\n File Names is: %s \n ", completePathOuput);
					getch();
					return;
			}

/**************** Execute the Live Recording Module ****************/

			system(liveRecordingCommand);		//execute the command
			 
			//printf("\n Playing Your Sound: "); 
			//PlaySound(TEXT(liveRecordingWAV), NULL, SND_APPLICATION );

			printf("\n\n <-------->\n\n");
			fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TESTING LANG: %s < ----------------------- \n",liveRecordingFileName );
/**************** Live Testing ****************/
			gui_lang_index = live_testing_playlist(model_type_use, lang_index_begin);
/**************** SHOW Playlist ****************/

			if(gui_lang_index==-1)
			{
				this->lang_result->Text = L"PLAYLIST NOT RECOGNIZED";
				return;
			}

			 this->lang_result->Text = gcnew String(strupr(HMM_WORDS[gui_lang_index]));

				this->LABEL_SONG0->Text += gcnew String(playlist_songs_arr[gui_lang_index][0]);
				this->LABEL_SONG1->Text += gcnew String(playlist_songs_arr[gui_lang_index][1]);
				this->LABEL_SONG2->Text += gcnew String(playlist_songs_arr[gui_lang_index][2]);
				this->LABEL_SONG3->Text += gcnew String(playlist_songs_arr[gui_lang_index][3]);
				this->LABEL_SONG4->Text += gcnew String(playlist_songs_arr[gui_lang_index][4]);
			
		
			this->button_speak_index->BackColor = System::Drawing::Color::MediumAquamarine;
			this->button_speak_index->ForeColor = System::Drawing::Color::DarkMagenta;
			this->button_speak_index->Enabled = true;


		printf("\n\n----------------------------------- LANG SELECT END ---------------------------------------\n\n\n");
		
		fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
		fprintf(fp_console, "\n <---------------------------------- ----------------------------------> LANG SELECT END <---------------------------------- -------------------------------------->"); 
		fflush(fp_console); fclose(fp_console); 
			
		printf("\n\n Language Detection Complete. Returned To GUI.");
	}// function to detect language

//SPEAK INDEX
	private: System::Void button_speak_index_Click(System::Object^  sender, System::EventArgs^  e) {

		char path_folder[300];	//for song open
		char model_type_string[20] = "new_model";	//which model is used
		unsigned int model_type_use = OutputFolderModel;	

		this->label_playing_now->Text = L"Playing Right Now: ";

		printf("\n\n\n <-------->");
		printf("\n Duration 3 sec: RECORDING INDEX: \n");

		/**************** Creating necessary file Path for data. ****************/
		sprintf(liveRecordingFileName, "gui_playlist_livetest_%ld_index", gui_timestamp);  //file_name
		sprintf(liveRecordingCommand, "%s 3 %s %s%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
		sprintf(completePathOuput, "%s%s_testresult_%s.txt", input_live_voice_folder, liveRecordingFileName ,model_type_string);  
			/**************** Opening respective files. ****************/
			fp_console = fopen(completePathOuput, "a");					//to read input observation sequence
			if(fp_console == NULL){ 
					perror("\n Error: ");
					printf("\n File Names is: %s \n ", completePathOuput);
					getch();
					return;
			}
		/**************** Execute the Live Recording Module ****************/
		system(liveRecordingCommand);		//execute the command
		
		//printf("\n Playing Your Sound: "); 
		//PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );

		fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TESTING INDEX: %s < ----------------------- \n",liveRecordingFileName );

		/**************** Live Testing ****************/
		gui_song_index = live_testing_playlist(model_type_use, 0);
		/**************** Play Songs ****************/

		printf("\n\n <-------->\n\n ");
		sprintf(path_folder, "\"SONGS\\%s\\%s\"", HMM_WORDS[gui_lang_index], playlist_songs_arr[gui_lang_index][gui_song_index]);  //file_name
		printf("\n PLAYING SONG: ");
		printf("%s\n", path_folder);

		this->label_playing_now->Text += gcnew String(playlist_songs_arr[gui_lang_index][gui_song_index]);


		system(path_folder); // open default music player to play the song

		//gui_song_index++; /////////////////////////////////////////////////////////////

		printf("\n\n----------------------------------- SONG SELECT END ---------------------------------------\n\n\n");
		fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
		fprintf(fp_console, "\n <---------------------------------- ----------------------------------> SONG SELECT END <---------------------------------- -------------------------------------->"); 
		fflush(fp_console); fclose(fp_console); 

		gui_timestamp = time(NULL);
		printf("\n Index Detection Complete. Returned To GUI.");
	} //Select song index

//RESET SONGS
	private: System::Void button_reset_Click(System::Object^  sender, System::EventArgs^  e) {
				this->Test_Lang->Enabled = true;
				this->Test_Lang->BackColor = System::Drawing::Color::MediumAquamarine;
				this->Test_Lang->ForeColor = System::Drawing::Color::DarkMagenta;
			
				this->button_speak_index->Enabled = false;
				this->button_speak_index->BackColor = System::Drawing::Color::LightGray;
				this->button_speak_index->ForeColor = System::Drawing::Color::Gray;
			
				this->LABEL_SONG0->Text = L"0. ";
				this->LABEL_SONG1->Text = L"1. ";
				this->LABEL_SONG2->Text = L"2. ";
				this->LABEL_SONG3->Text = L"3. ";
				this->LABEL_SONG4->Text = L"4. ";

				this->lang_result->Text = L"-";
				this->label_playing_now->Text = L"";
				gui_lang_index = 6;
		 }//RESET SONGS

//CONSOLE BUTTON
	private: System::Void console_app_Click(System::Object^  sender, System::EventArgs^  e) {
				console_main();
				printf("\n\n Control Returned To GUI.");

				lang_listview->Items->Clear();
				for(int lg=lang_index_begin; lg<totWords;lg++)
				{
				  ListViewItem^ item1 = gcnew ListViewItem( gcnew String(strupr(HMM_WORDS[lg])),0 );
				  item1->SubItems->Add( lg.ToString() );
				  lang_listview->Items->Add( item1 );
				  lang_listview->Items[ lg-lang_index_begin ]->Selected = false;
				}
	}// Console App

//LT 0
private: System::Void live_train_index0_Click(System::Object^  sender, System::EventArgs^  e) {
			LiveRecordingTrainingTheOutputModel(0);	
			printf("\n\n Word 'Zero' Converged. Returned To GUI.");
		}
//LT 1
private: System::Void live_train_index1_Click(System::Object^  sender, System::EventArgs^  e) {
			 	LiveRecordingTrainingTheOutputModel(1);	
			printf("\n\n Word 'One' Converged. Returned To GUI.");
		 }
//LT 2
private: System::Void live_train_index2_Click(System::Object^  sender, System::EventArgs^  e) {
			 	LiveRecordingTrainingTheOutputModel(2);	
			printf("\n\n Word 'Two' Converged. Returned To GUI.");
		 }
//LT 3
private: System::Void live_train_index3_Click(System::Object^  sender, System::EventArgs^  e) {
			 	LiveRecordingTrainingTheOutputModel(3);
			printf("\n\n Word 'Three' Converged. Returned To GUI.");
		 }
//LT 4
private: System::Void live_train_index4_Click(System::Object^  sender, System::EventArgs^  e) {
			 	LiveRecordingTrainingTheOutputModel(4);	
			printf("\n\n Word 'Four' Converged. Returned To GUI.");
		 }
//LT 5 Hindi	
	private: System::Void liveTrain_hindi_Click(System::Object^  sender, System::EventArgs^  e) {
				LiveRecordingTrainingTheOutputModel(lang_index_begin);	
		printf("\n\n Word 'Hindi' Converged. Returned To GUI.");
	}//liveTrain_hindi_Click

//LT 6 English	
	private: System::Void liveTrain_English_Click(System::Object^  sender, System::EventArgs^  e) {
				LiveRecordingTrainingTheOutputModel(lang_index_begin+1);	
		printf("\n\n Word 'English' Converged. Returned To GUI.");
	}//liveTrain_English_Click

//List View Index Changed
	private: System::Void lang_listview_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				this->LiveTrain_Lang_new->Visible=true;
				if (lang_listview->SelectedIndices->Count <= 0) 
				{ 
					return; 
				} 
				int intselectedindex = lang_listview->SelectedIndices[0]; 
				if (intselectedindex >= 0) 
				{
					this->LiveTrain_Lang_new->Text = "LT "+lang_listview->Items[intselectedindex]->Text;
				} 
	}


	private: System::Void LiveTrain_Lang_new_Click(System::Object^  sender, System::EventArgs^  e) {

		this->LiveTrain_Lang_new->Visible=false;
		int intselectedindex1 = lang_listview->SelectedIndices[0]; 
		int word_index = System::Convert::ToInt32(lang_listview->Items[intselectedindex1]->SubItems[1]->Text) ;
		LiveRecordingTrainingTheOutputModel(word_index);
		printf("\n\n Word '%s' [%d] Converged. Returned To GUI.",lang_listview->Items[intselectedindex1]->Text,word_index);

		
	}
};
}
